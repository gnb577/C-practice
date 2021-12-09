#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <Winuser.h>

using namespace std;

class CDlg
{
private:
	int parm_message_type;
	char* parm_data;
	int parm_size;
public:
	BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

};

BOOL CDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	COPYDATASTRUCT* p_tip = pCopyDataStruct;
	CString	is_parm = (char*)p_tip->lpData;
	CStringArray str_array;

	if (p_tip->dwData == 200001) {	// 메세지 번호
		AfxMessageBox(is_parm);
	}

	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

