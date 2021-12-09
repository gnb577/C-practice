#include <iostream>  
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;
class Book {
	string title; // 책 이름
	string author; // 저자
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
	cout << year << "년도, " << title << ", " << author << endl;
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
	cout << "검색하고자 하는 저자 이름을 입력하세요~" << endl;
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
				cout << "총 입고된 책은 " << bookcnt << "권입니다." << endl;
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

