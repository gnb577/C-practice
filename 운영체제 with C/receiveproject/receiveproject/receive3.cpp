// Ÿ�̸Ӹ� �߻�����, �׶����� ��ƽ�� ���� ��ġ�� ����ϴ�(���ӵ� ���� ��������) �ٿ ������ ���α׷�

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
LPCTSTR lpszClass = TEXT("Bounce1"); //������ â�� ����

RECT crt;
int x, y;
int xv, yv;
int flag = 0;
int btnflag = 0;



struct trans_struct {
	int x;
	int y;
	int xv;
	int yv;
}trans_struct;

struct trans_struct data = { 0, };
void moveBall();
void update();
void receive();



//������ ���α׷��� ����(���ø�)
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

//���� �ݺ������� ���ư��� �κ�(�Լ�����) -> �޽����� ���������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	COPYDATASTRUCT* pcds;
	switch (iMessage) {
	case WM_CREATE:
		DoCreateMain(hWnd);
		break;
	case WM_PAINT:
		DoPaintMain(hWnd);
		break;
	case WM_LBUTTONDOWN: //���� ���콺�� ����������
		DoButtonMain(hWnd);
		break;
	case WM_TIMER: //���ϴ� �ð� 
		OnTimer(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, 0);
		CloseHandle(hThread);
		return(0);
	case WM_COPYDATA:
		update();
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void DoCreateMain(HWND hWnd)
{
	GetClientRect(hWnd, &crt);
	crt.left = 401;
	crt.right = 800;
	crt.top = 400;
	crt.bottom = 0;

	x = 80;	//���� x ��ǥ �ʱⰪ
	y = 250;//���� y ��ǥ �ʱⰪ

	xv = (rand() % 4) + 5; //x���� �ӵ�
	yv = (rand() % 4) + 5; //y���� �ӵ�
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
		MessageBox(hWnd, TEXT("���α׷��� ����Ǿ����ϴ�."), TEXT("OK"), MB_OK);
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
	Ellipse(hMemDC, x - R, y - R, x + R, y + R);	 //���׸���

	hBrush = CreateSolidBrush(RGB(255, 255, 0));
	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	
	DeleteObject(SelectObject(hMemDC, OldPen));
	DeleteObject(SelectObject(hMemDC, OldBrush));

	wsprintf(str, TEXT("%d, %d, %d, %d"), x, y, xv, yv);
	TextOut(hMemDC, 100, 50, str, lstrlen(str));

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hdc);
	InvalidateRect(hWnd, NULL, FALSE);

	moveBall();  //���� ������

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


void update()
{
	x = data.x;
	y = data.y;
	xv = data.xv;
	yv = data.yv;
	return;
}