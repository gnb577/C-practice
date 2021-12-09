//Send--------------
#include <windows.h>


HWND hWnd = ::FindWindow(0, TEXT("제목없음 - mfcEx"));
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

//WM_COPYDATA를 case해서 적용.



BOOL CMainFrame::OnCopyData(CWnd * pWnd, COPYDATASTRUCT * pCopyDataStruct)
{
    // TODO: Add your message handler code here and/or call default

    TRACE0("1111\n");
    TRACE1("%s\n", (char*)pCopyDataStruct->lpData);
    return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

// MFC에서 적용할시 프레임인지 뷰인지 잘 생각해야 함.
[출처] WM_COPYDATA 사용법. | 작성자 운주니