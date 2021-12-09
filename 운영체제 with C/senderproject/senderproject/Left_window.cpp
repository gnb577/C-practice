// Ÿ�̸Ӹ� �߻�����, �׶����� ��ƽ�� ���� ��ġ�� ����ϴ�(���ӵ� ���� ��������) �ٿ ������ ���α׷�

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadFunc(LPVOID prc);
DWORD WINAPI ThreadMovingBall(PVOID pArg);
void DoCreateMain(HWND hWnd);
void DoButtonMain(HWND hWnd);
void DoPaintMain(HWND hWnd);
void OnTimer(HWND hWnd);

#define R 20	//���� ������
#define BOUNCE 1	//���� ��ȯ�� ���


HBITMAP hBit;
HINSTANCE g_hInst;
HWND hWndMain, hWnd2;
HANDLE hThread;
LPCTSTR lpszClass = TEXT("Bounce1"); //������ â�� ����

RECT crt;	//consoleâ�� ���� ������ ����
int x, y;	//���� x,y��ǥ
int xv, yv;	//���� �ӵ� ����
int flag = 0;//ȭ���� ���� ���� Ȯ�� flag �� ���⼭�� ������� ����
int btnflag = 0; // ��ư Ŭ�� Ƚ�� flag

PCOPYDATASTRUCT pMyCDS; //receive�� �� ����� pointer copydata

struct trans_struct    //���� �����ؾ� �� �����͸� ����ü�� ǥ��
{
	int x;
	int y;
	int xv;
	int yv;
};	

void moveBall();	//(���� �� �̵�)moveball() + �� ƨ���(collision�� �Ϻ�)


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
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
		NULL, (HMENU)NULL, hInstance, NULL);
	//â ũ���� ���� 500x500���� ����
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
	switch (iMessage) { //�޽����� ������ ���� �ൿ���� caseȭ ��
	case WM_CREATE:
		DoCreateMain(hWnd);
		break;
	case WM_PAINT:
		DoPaintMain(hWnd);
		break;
	case WM_LBUTTONDOWN: //���� ���콺�� ����������
		DoButtonMain(hWnd);
		break;
	case WM_COPYDATA:
		pMyCDS = (PCOPYDATASTRUCT)lParam; // ���� ���� pointer���·� �޾ƾ��ؼ� (�����ͷ� ������ ���� ���μ����� �ƴϴ� ������ ���� ����)
		if (pMyCDS->dwData) // copydata���� data�� �����ϴ� �κ� , x,y,xv,yv�� ��� ����
		{
			x = (int)((trans_struct*)(pMyCDS->lpData))->x; // LVOID�̱� ������ ������Ÿ���� �������־���ϰ�, ���� ���� ���� INTEGER���̱� ������ 
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

void send() { //������ �۽�
	
	HWND m_Window = ::FindWindow(NULL, TEXT("Bounce2")); //�۽��� â�� �̸��� ����

	COPYDATASTRUCT copyData; //copydata�� �̿��� ������ ������ ����

	trans_struct data;	//�̸� �غ�� ���ۿ� ����ü�� Ȱ���ؼ� ���� �����ϰ� �ִ� ���� ���� ����
	data.x = x;
	data.y = y;
	data.xv = xv;
	data.yv = yv;

	copyData.dwData = 1;	//protocol Ȥ�� socket number��� �����ϸ� �� �� ����.
	copyData.cbData = sizeof(data);	//�ش� ������(����ü)�� �� ũ��
	copyData.lpData = &data; //����ü�� �ּ�

	::SendMessage(m_Window, WM_COPYDATA, (WPARAM)(HWND)hWndMain, (LPARAM)(LPVOID)&copyData); //�����Լ�
	//�ش� ������ or class��, �׸��� ������ �޽���, �׸��� �������� �޽����� �ΰ������ε�, ������ �κ��� copydata�� ������ �ִ� �ּҸ� ��Ÿ��
}

void DoCreateMain(HWND hWnd)
{
	//������� handle, ���� ������ �����̰� �� <- �Ϻ��� collision�� �������
	HANDLE hThreadMovingBall = CreateThread(NULL, 0, ThreadMovingBall, (PVOID)hWndMain, 0, NULL);
	CloseHandle(hThreadMovingBall);

	GetClientRect(hWnd, &crt);

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
	if (btnflag == 0) {//���� ��ư �Է½� ������ ���� �۾�
		MessageBox(hWnd, TEXT("���α׷��� ����Ǿ����ϴ�."), TEXT("OK"), MB_OK);
		SetTimer(hWnd, 1, 25, NULL);
	}
	if (btnflag > 0) {//���Ĵ� ���� ������ �ٲٸ鼭 ����
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

	wsprintf(str, TEXT("%d, %d, %d, %d"), x, y, xv, yv); // x,y,xv,yv�� ���� print����
	TextOut(hMemDC, 100, 50, str, lstrlen(str));

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hdc);
	InvalidateRect(hWnd, NULL, FALSE);

	moveBall();  //���� �����̰�
	//send(); //���� ������ ������ ���� ���� ������ , ���ۿ� ����ü�� ���� --> �׷����� ���� ���μ������� ����ϱ� ���� ���� ���� �޸𸮿� �����ϴ� ����
}

void moveBall()//�����°� ��������
{
	if (y <= crt.top + R || y >= crt.bottom - R) { //top+�������� �Ѿ�ų�, bottom+�������� �Ѿ�� �ʵ��� ���ǰɾ���
		yv *= -(BOUNCE);
		if (y <= R) y = crt.top + R;
		if (y >= crt.bottom - R) y = crt.bottom - R;
	}
	if (x <= crt.left + R) {	//�¸� ���������� ������ ����
		xv *= -(BOUNCE);
		x = crt.left + R;
	}
	x += (int)xv;
	y += (int)yv;
	if (x < 500) {	//������ ��ǥ�� 0~500���� ��Ƽ� ���� â�� ���� ���� ���� ������ �Ѱ���
		send(); //���� ������ ������ ���� ���� ������, ���ۿ� ����ü�� ����-- > �׷����� ���� ���μ������� ����ϱ� ���� ���� ���� �޸𸮿� �����ϴ� ����
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
