// 타이머를 발생시켜, 그때마다 스틱과 공의 위치를 계산하는(가속도 등이 전혀없는) 바운스 윈도우 프로그램

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadFunc(LPVOID prc);
DWORD WINAPI ThreadMovingBall();
DWORD WINAPI ThreadStick();
DWORD WINAPI ThreadCollision();

void DoCreateMain(HWND hWnd);
void DoButtonMain(HWND hWnd);
void DoPaintMain(HWND hWnd);
void OnTimer(HWND hWnd);

#define R 20	//원의 반지름
#define BOUNCE 1	//방향 전환용 상수
#define W 20	//stick의 폭
#define H 200 //stick의 길이

HBITMAP hBit;
HINSTANCE g_hInst;
HWND hWndMain, hWnd2;
HANDLE hThread;
LPCTSTR lpszClass = TEXT("Bounce");

RECT crt;	//console창의 범위 설정용 변수
int x, y;	//공의 x,y좌표
int xv, yv;	//공의 속도 변수
int flag = 0; //화면의 존재 여부 확인 flag
int btnflag = 0; //버튼 클릭 횟수 flag

int sX[2];// 스틱의 좌표를 저장할 변수
int sY[2];

float sXv[2];// 스틱의 속도를 저장할 변수
float sYv[2];


struct trans_struct { //서로 공유해야 될 데이터를 구조체로 표현, 단 이번 파트에서는 사용하지 않음
	int x;
	int y;
	int xv;
	int yv;
}trans_struct;


void moveStick(); //스틱 이동
void moveBall(); //공 이동
void collision(); // 충돌

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_BORDER | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	hWndMain = hWnd;

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	COPYDATASTRUCT* pcds; // copydata는 이후에 사용되기에 미사용

	switch (iMessage) { //메시지의 종류에 따른 행동들을 case화 함

	case WM_CREATE:
		DoCreateMain(hWnd);
		break;
	case WM_PAINT:
		DoPaintMain(hWnd);
		break;
	case WM_LBUTTONDOWN://왼쪽 마우스가 눌러졌을때
		DoButtonMain(hWnd);
		break;
	case WM_TIMER:
		OnTimer(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, 0);
		CloseHandle(hThread);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); //아직까지는 필요없음 통신에 필요한 return값
}

void DoCreateMain(HWND hWnd)
{
	GetClientRect(hWnd, &crt);

	//쓰레드용 handle, 각각 공과 스틱을 별도로 움직이게 함
	HANDLE hThreadMovingBall = CreateThread(NULL, 0, ThreadMovingBall, (PVOID)hWndMain, 0, NULL);
	HANDLE hThreadStick = CreateThread(NULL, 0, ThreadStick, (PVOID)hWndMain, 0, NULL);
	//HANDLE hThreadCollision = CreateThread(NULL, 0, ThreadCollision, (PVOID)hWndMain, 0, NULL);


	//WaitForMultipleObjects(2, hThreadStick,hThreadMovingBall,TRUE, INFINITE);

	CloseHandle(hThreadMovingBall);
	CloseHandle(hThreadStick);
	//CloseHandle(ThreadCollision);

	x = 80;	//공의 x 좌표 초기값
	y = 250;//공의 y 좌표 초기값

	xv = (rand() % 4) + 5; //x벡터 속도
	yv = (rand() % 4) + 5; //y벡터 속도


	sX[0] = 0; sY[0] = H; //왼쪽 스틱 초기값
	sXv[0] = 210; sYv[0] = 5; //왼쪽 스틱 속도

	sX[1] = crt.right - W; sY[1] = H - 50; //오른쪽 스틱 초기값
	sXv[1] = 110; sYv[1] = 10; //오른쪽 스틱 속도
}

void DoPaintMain(HWND hWnd)
{
	HDC hdc, hMemDC;
	PAINTSTRUCT ps;
	HBITMAP OldBit;

	hdc = BeginPaint(hWnd, &ps);

	hMemDC = CreateCompatibleDC(hdc);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);
	BitBlt(hdc, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	EndPaint(hWnd, &ps);
	return;
}

void DoButtonMain(HWND hWnd)
{
	if (btnflag == 0) { //최초 버튼 입력시 다음과 같은 작업
		MessageBox(hWnd, TEXT("프로그램이 실행되었습니다."), TEXT("OK"), MB_OK);
		SetTimer(hWnd, 1, 25, NULL);
	}
	if (btnflag > 0) { //이후는 공의 방향을 바꾸면서 생성
		x = 250;
		y = 200;
		xv *= -(BOUNCE);
		flag = 0;
	}
	btnflag = 1;

}

void OnTimer(HWND hWnd)
{
	TCHAR str[123];
	HDC hdc, hMemDC;
	HBITMAP OldBit;
	HPEN hPen, OldPen;
	HBRUSH hBrush, OldBrush;

	hdc = GetDC(hWnd);
	GetClientRect(hWnd, &crt);
	if (hBit == NULL)
	{
		hBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	}
	hMemDC = CreateCompatibleDC(hdc);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));

	hPen = CreatePen(PS_INSIDEFRAME, 2, RGB(0, 0, 0));
	OldPen = (HPEN)SelectObject(hMemDC, hPen);
	hBrush = CreateSolidBrush(RGB(255, 120, 0));
	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	Ellipse(hMemDC, x - R, y - R, x + R, y + R);	 //공그리기


	hBrush = CreateSolidBrush(RGB(255, 255, 0));
	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	Rectangle(hMemDC, sX[0], sY[0], sX[0] + W, sY[0] + H); //스틱 그리기
	Rectangle(hMemDC, sX[1], sY[1], sX[1] + W, sY[1] + H); //스틱 그리기


	DeleteObject(SelectObject(hMemDC, OldPen));
	DeleteObject(SelectObject(hMemDC, OldBrush));

	wsprintf(str, TEXT("%d, %d, %d, %d"), x, y, xv, yv);
	TextOut(hMemDC, 100, 50, str, lstrlen(str));


	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hdc);
	InvalidateRect(hWnd, NULL, FALSE);

	//moveStick(); //스틱의 움직임
	//moveBall();  //공의 움직임
	collision();



}


void moveBall()
{
	if (y <= R || y >= crt.bottom - R) { //상단 혹은 하단부에 걸렸을 경우 최대치를 유지한 채 역방향 진행
		yv *= -(BOUNCE);
		if (y <= R) y = R;
		if (y >= crt.bottom - R) y = crt.bottom - R;
	}
	x += (int)xv;
	y += (int)yv;

}

void moveStick()
{
	RECT crt;
	GetClientRect(hWndMain, &crt); 
	//공과 마찬가지로 상하 단부의 끝에 걸렸을 경우 방향전환 (bounce를 썼어도 문제 없을듯하다)
	if (sY[0] <= 0 || sY[0] >= crt.bottom - H)
	{
		sYv[0] *= -1;
	}

	if (sY[1] <= 0 || sY[1] >= crt.bottom - H)
	{
		sYv[1] *= -1;
	}

	sY[0] += sYv[0];
	sY[1] += sYv[1];

}

DWORD WINAPI ThreadMovingBall()
{
	Sleep(50);
	while (1)
	{
		Sleep(30);
		moveBall();
	}

}

DWORD WINAPI ThreadStick()
{
	Sleep(100);
	while (1)
	{
		Sleep(30);
		moveStick();
	}

}



void collision() //부딪혔을 경우와 벗어난 경우로 분리
{
	if (flag == 0) 
	{

		if (x < W + R && y > sY[0] - R && y < sY[0] + H + R) //왼쪽 막대에 부딪힌 경우, 역방향으로 값과 방향을 바꾸어줌
		{
			x += R / 2;
			xv *= (-BOUNCE);
		}
		if (x >= crt.right - R - W && y > sY[1] - R && y < sY[1] + H + R)//오른쪽 막대에 부딪힌 경우, 역방향으로 값과 방향을 바꾸어줌
		{
			x -= R / 2;
			xv *= (-BOUNCE);
		}
	}

	if (x < crt.left - R || x > crt.right + R) //벗어난 경우
	{
		flag = 1;
	}
}


DWORD WINAPI ThreadCollision()
{
	Sleep(100);
	while (1)
	{
		Sleep(30);
		collision();
	}

}