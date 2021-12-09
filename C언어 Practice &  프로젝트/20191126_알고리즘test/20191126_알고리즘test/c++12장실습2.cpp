#include <iostream>
#include <fstream>
#include <string>
//안되요 다시해봅시다
using namespace std;
int main() {
	ifstream fin("c:\\windows\\system.ini");
	if (!fin) {
		cout << "c:\\windows\\system.ini 열기 오류";
		return 0;
	}
	ofstream fout("system.txt");
	if (!fout)
	{
		cout << "system.txt 열기 오류";
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
