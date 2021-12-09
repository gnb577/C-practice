#include <stdio.h>
#include <windows.h>
#include <iostream>

using namespace std;

class CDlg
{
private:
	int parm_message_type;
	char* parm_data;
	int parm_size;
public:
	int SendDataMessage(int parm_message_type, char* parm_data, int parm_size);

};


// int parm_message_type : 메세지ID

// char *parm_data : 전송할 프로토콜

// int parm_size : 전송할 크기

int CDlg::SendDataMessage(int parm_message_type, char* parm_data, int parm_size)

{

	int return_value = 0;

	HWND is_des_hwnd = ::FindWindow(_T("대상클래스"), NULL);



	if (is_des_hwnd != NULL) {

		char* p_buffer = new char[parm_size + 1];

		memset(p_buffer, 0, parm_size + 1);

		if (p_buffer != NULL) {

			memcpy(p_buffer, parm_data, parm_size);

			COPYDATASTRUCT tip;

			tip.dwData = parm_message_type;

			tip.cbData = parm_size;

			tip.lpData = p_buffer;

			return_value = ::SendMessage(is_des_hwnd, WM_COPYDATA, (WPARAM)this->m_hWnd, (LPARAM)&tip);

			delete p_buffer;	p_buffer = NULL;

		}

	}



	return return_value;

}

