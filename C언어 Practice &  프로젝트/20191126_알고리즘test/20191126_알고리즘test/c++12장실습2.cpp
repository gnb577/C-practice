#include <iostream>
#include <fstream>
#include <string>
//�ȵǿ� �ٽ��غ��ô�
using namespace std;
int main() {
	ifstream fin("c:\\windows\\system.ini");
	if (!fin) {
		cout << "c:\\windows\\system.ini ���� ����";
		return 0;
	}
	ofstream fout("system.txt");
	if (!fout)
	{
		cout << "system.txt ���� ����";
	}
	char arr[500];
	int ch;
	string line;
	while (ch = fin.get() != EOF) {
		char a = ch;
		if (a >= 'a' && a <= 'z')
		{
			a = a - 20;
		}
		fout.put(a);
	}
	fin.close();
	fout.close();

}
