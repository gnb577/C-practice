// 타이머를 발생시켜, 그때마다 스틱과 공의 위치를 계산하는(가속도 등이 전혀없는) 바운스 윈도우 프로그램

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadFunc(LPVOID prc);
DWORD WINAPI ThreadMovingBall(PVOID pArg);
void DoCreateMain(HWND hWnd);
void DoButtonMain(HWND hWnd);
void DoPaintMain(HWND hWnd);
void OnTimer(HWND hWnd);

#define R 20	//원의 반지름
#define BOUNCE 1	//방향 전환용 상수


HBITMAP hBit;
HINSTANCE g_hInst;
HWND hWndMain, hWnd2;
HANDLE hThread;
LPCTSTR lpszClass = TEXT("Bounce1"); //윈도우 창의 제목

RECT crt;	//console창의 범위 설정용 변수
int x, y;	//공의 x,y좌표
int xv, yv;	//공의 속도 변수
int flag = 0;//화면의 존재 여부 확인 flag 단 여기서는 사용하지 않음
int btnflag = 0; // 버튼 클릭 횟수 flag

PCOPYDATASTRUCT pMyCDS; //receive할 때 사용할 pointer copydata

struct trans_struct    //서로 공유해야 될 데이터를 구조체로 표현
{
	int x;
	int y;
	int xv;
	int yv;
};	

void moveBall();	//(원래 공 이동)moveball() + 벽 튕기기(collision의 일부)


//윈도우 프로그램의 시작(템플릿)
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
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
		NULL, (HMENU)NULL, hInstance, NULL);
	//창 크기의 제한 500x500으로 생성
	ShowWindow(hWnd, nCmdShow);
	hWndMain = hWnd;

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


//실제 반복적으로 돌아가는 부분(함수집합) -> 메시지가 있을때마다 동작
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) { //메시지의 종류에 따른 행동들을 case화 함
	case WM_CREATE:
		DoCreateMain(hWnd);
		break;
	case WM_PAINT:
		DoPaintMain(hWnd);
		break;
	case WM_LBUTTONDOWN: //왼쪽 마우스가 눌러졌을때
		DoButtonMain(hWnd);
		break;
	case WM_COPYDATA:
		pMyCDS = (PCOPYDATASTRUCT)lParam; // 보낸 값을 pointer형태로 받아야해서 (데이터로 받으면 같은 프로세스가 아니니 공유가 쉽지 않음)
		if (pMyCDS->dwData) // copydata에서 data를 관장하는 부분 , x,y,xv,yv가 들어 있음
		{
			x = (int)((trans_struct*)(pMyCDS->lpData))->x; // LVOID이기 때문에 데이터타입을 지정해주어야하고, 내가 받을 값이 INTEGER형이기 때문에 
			y = (int)((trans_struct*)(pMyCDS->lpData))->y;
			xv = (int)((trans_struct*)(pMyCDS->lpData))->xv;
			yv = (int)((trans_struct*)(pMyCDS->lpData))->yv;
		}
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
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void send() { //데이터 송신
	
	HWND m_Window = ::FindWindow(NULL, TEXT("Bounce2")); //송신할 창의 이름을 지정

	COPYDATASTRUCT copyData; //copydata를 이용해 데이터 전송할 예정

	trans_struct data;	//미리 준비된 전송용 구조체를 활용해서 현재 보유하고 있는 값을 집어 넣음
	data.x = x;
	data.y = y;
	data.xv = xv;
	data.yv = yv;

	copyData.dwData = 1;	//protocol 혹은 socket number라고 생각하면 될 거 같다.
	copyData.cbData = sizeof(data);	//해당 데이터(구조체)의 총 크기
	copyData.lpData = &data; //구조체의 주소

	::SendMessage(m_Window, WM_COPYDATA, (WPARAM)(HWND)hWndMain, (LPARAM)(LPVOID)&copyData); //전송함수
	//해당 윈도우 or class명, 그리고 보내는 메시지, 그리고 나머지는 메시지의 부가정보인데, 마지막 부분은 copydata를 가지고 있는 주소를 나타냄
}

void DoCreateMain(HWND hWnd)
{
	//쓰레드용 handle, 공을 별도로 움직이게 함 <- 일부의 collision도 들어있음
	HANDLE hThreadMovingBall = CreateThread(NULL, 0, ThreadMovingBall, (PVOID)hWndMain, 0, NULL);
	CloseHandle(hThreadMovingBall);

	GetClientRect(hWnd, &crt);

	x = 80;	//공의 x 좌표 초기값
	y = 250;//공의 y 좌표 초기값

	xv = (rand() % 4) + 5; //x벡터 속도
	yv = (rand() % 4) + 5; //y벡터 속도

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
	if (btnflag == 0) {//최초 버튼 입력시 다음과 같은 작업
		MessageBox(hWnd, TEXT("프로그램이 실행되었습니다."), TEXT("OK"), MB_OK);
		SetTimer(hWnd, 1, 25, NULL);
	}
	if (btnflag > 0) {//이후는 공의 방향을 바꾸면서 생성
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

	DeleteObject(SelectObject(hMemDC, OldPen));
	DeleteObject(SelectObject(hMemDC, OldBrush));

	wsprintf(str, TEXT("%d, %d, %d, %d"), x, y, xv, yv); // x,y,xv,yv의 값을 print해줌
	TextOut(hMemDC, 100, 50, str, lstrlen(str));

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hdc);
	InvalidateRect(hWnd, NULL, FALSE);

	moveBall();  //공을 움직이고
	//send(); //공을 움직인 직후의 값을 공유 데이터 , 전송용 구조체에 저장 --> 그로인해 다음 프로세스에서 사용하기 위한 값을 공유 메모리에 저장하는 개념
}

void moveBall()//상하좌가 막혀있음
{
	if (y <= crt.top + R || y >= crt.bottom - R) { //top+반지름을 넘어가거나, bottom+반지름을 넘어가지 않도록 조건걸어줌
		yv *= -(BOUNCE);
		if (y <= R) y = crt.top + R;
		if (y >= crt.bottom - R) y = crt.bottom - R;
	}
	if (x <= crt.left + R) {	//좌만 막혀있으니 좌측만 보정
		xv *= -(BOUNCE);
		x = crt.left + R;
	}
	x += (int)xv;
	y += (int)yv;
	if (x < 500) {	//좌측의 좌표를 0~500으로 잡아서 좌측 창에 공이 있을 때만 정보를 넘겨줌
		send(); //공을 움직인 직후의 값을 공유 데이터, 전송용 구조체에 저장-- > 그로인해 다음 프로세스에서 사용하기 위한 값을 공유 메모리에 저장하는 개념
	}
}

DWORD WINAPI ThreadMovingBall(PVOID pArg)
{
	while (1)
	{
		Sleep(200);
		moveBall();
	}
	return 0;
}
