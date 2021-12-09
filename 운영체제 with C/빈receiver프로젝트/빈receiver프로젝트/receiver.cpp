// 타이머를 발생시켜, 그때마다 스틱과 공의 위치를 계산하는(가속도 등이 전혀없는) 바운스 윈도우 프로그램

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadFunc(LPVOID prc);
void DoCreateMain(HWND hWnd);
void DoButtonMain(HWND hWnd);
void DoPaintMain(HWND hWnd);
void OnTimer(HWND hWnd);

#define R 20
#define BOUNCE 1
#define W 20
#define H 200

HBITMAP hBit;
HINSTANCE g_hInst;
HWND hWndMain, hWnd2;
HANDLE hThread;
LPCTSTR lpszClass = TEXT("Bounce1"); //윈도우 창의 제목

RECT crt;
int x, y;
int xv, yv;
int flag = 0;
int btnflag = 0;

int sX[2];
int sY[2];

float sXv[2];
float sYv[2];

struct trans_struct {
	int x;
	int y;
	int xv;
	int yv;
}trans_struct;
void moveStick();
void moveBall();
void collision();

struct stBuf {
	int n;
	char c[256];
};
stBuf buf;

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

//실제 반복적으로 돌아가는 부분(함수집합) -> 메시지가 있을때마다 동작
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	COPYDATASTRUCT* pcds;
	switch (iMessage) {
	case WM_CREATE:
		DoCreateMain(hWnd);
		break;
	case WM_PAINT:
		DoPaintMain(hWnd);
		break;
	case WM_LBUTTONDOWN: //왼쪽 마우스가 눌러졌을때
		DoButtonMain(hWnd);
		break;
	case WM_TIMER: //원하는 시간 
		OnTimer(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, 0);
		CloseHandle(hThread);
		return 0;
	case WM_COPYDATA:
		//stBuf* buf = (stBuf*)(pCopyDataStruct->lpData);
		//return CDialog::OnCopyData(pWnd, pcopyData);
		return 0;

	case WM_USER + 1:
		MessageBox(hWnd, TEXT("메시지를 받음"), TEXT("알림"), MB_OK);
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void DoCreateMain(HWND hWnd)
{
	GetClientRect(hWnd, &crt);

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
	if (btnflag == 0) {
		MessageBox(hWnd, TEXT("프로그램이 실행되었습니다."), TEXT("OK"), MB_OK);
		SetTimer(hWnd, 1, 25, NULL);
	}
	if (btnflag > 0) {
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

	moveStick(); //스틱의 움직임
	moveBall();  //공의 움직임
	collision();
}

void moveBall()
{
	if (y <= R || y >= crt.bottom - R) {
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
void collision()
{
	if (flag == 0) {
		if (x < W + R && y > sY[0] - R && y < sY[0] + H + R)
		{
			x += R / 2;
			xv *= (-BOUNCE);
		}
		if (x >= crt.right - R - W && y > sY[1] - R && y < sY[1] + H + R)
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
//
//BOOL Bounce1::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
//
//{
//
//	stBuf* buf = (stBuf*)(pCopyDataStruct->lpData);
//
//	// buf.n 과 buf.c[0~2]을 읽는다.
//
//
//
//	return CDialog::OnCopyData(pWnd, pcopyData);
//
//}