//Send--------------
#include <windows.h>


HWND hWnd = ::FindWindow(0, TEXT("������� - mfcEx"));
COPYDATASTRUCT cs;
char str[50] = "muzcity";
cs.dwData = hptr;
cs.lpData = &str;
cs.cbData = 50;

if (hWnd != NULL)
{
    if (::SendMessage(hWnd, WM_COPYDATA, (WPARAM)(HWND)this->m_hWnd, (LPARAM)(LPVOID)&cs) == TRUE)
    {
        TRACE0("Success\n");
    }
}

-------------------------------------------- -

recv---------------------------------------- -

//WM_COPYDATA�� case�ؼ� ����.



BOOL CMainFrame::OnCopyData(CWnd * pWnd, COPYDATASTRUCT * pCopyDataStruct)
{
    // TODO: Add your message handler code here and/or call default

    TRACE0("1111\n");
    TRACE1("%s\n", (char*)pCopyDataStruct->lpData);
    return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

// MFC���� �����ҽ� ���������� ������ �� �����ؾ� ��.
[��ó] WM_COPYDATA ����. | �ۼ��� ���ִ�