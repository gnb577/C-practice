#include <windows.h>
#include <stdio.h>
typedef struct tagMYREC
{
    char  s1[80];
    char  s2[80];
    DWORD n;
} MYREC;
PCOPYDATASTRUCT pMyCDS;
void WINAPI MyDisplay(LPSTR, LPSTR, DWORD);

    //
    // ************ Code fragment ****************
    //
switch (imessage)
{
case WM_COPYDATA:
    pMyCDS = (PCOPYDATASTRUCT)lParam;
    if (pMyCDS->dwData) {//�����Ͱ� �ִ� ���
       //LPCWSTR hs = (LPCWSTR)(DWORD)((stBuf*)(pMyCDS->lpData))->n;
        LPCWSTR hi = (LPCWSTR)(LPSTR)((stBuf)(pMyCDS->lpData.c[0];
        //LPCWSTR hi = (LPCWSTR)(LPSTR)((stBuf*)(pMyCDS->cbData));
        MessageBox(hWnd, hi, TEXT("�˸�"), MB_OK);
    }

}