#include <iostream>  
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;
class Book {
	string title; // å �̸�
	string author; // ����
	int year;
public:
	Book() {};
	Book(string title, string author, int year) :
		title(title), author(author), year(year) { }
	void set(string t, string a, int y) {
		title = t;
		author = a;
		year = y;
	}
	string getAuthor() { return author; }
	int getYear() { return year; }
	void show();
};
void Book::show() {
	cout << year << "�⵵, " << title << ", " << author << endl;
}


class BookManager {
	vector<Book> v;
	void searchByAuthor();
	void searchByYear();
	void bookIn();
public:
	void run();
};
//vector<Book> v;
void BookManager::searchByAuthor() {

	string authorname;
	cout << "�˻��ϰ��� �ϴ� ���� �̸��� �Է��ϼ���~" << endl;
	getline(cin, authorname);
	for (auto& b : v)
	{
		if (b.getAuthor() == authorname)
		{
			b.show();
		}
	}






}
void BookManager::searchByYear() {

	int bookyear;
	cin >> bookyear; 
	cin.ignore();
	for (auto& b : v)
	{
		if (b.getYear() == bookyear)
		{
			b.show();
		}
	}


}
//vector<Book> v;
void BookManager::bookIn()
{
	int bookcnt = 0;
		string bookname;
		string bookauthor;
		int bookyear=0;
		Book b;
		while(1)
		{
			if (bookyear == -1)
			{
				cout << "�� �԰�� å�� " << bookcnt << "���Դϴ�." << endl;
				break;
			}
			bookcnt++;
			getline(cin, bookname);
			getline(cin, bookauthor);
			cin >> bookyear;
			b.set(bookname, bookauthor, bookyear);
			v.push_back(b);
		}
}

