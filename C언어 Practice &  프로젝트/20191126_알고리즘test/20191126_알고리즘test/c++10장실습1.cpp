#include <iostream>  
#include <vector>
using namespace std;

class Circle {
	int x, y;
	int radius;
public:
	Circle() : x{ 0 }, y{ 0 }, radius{ 0 } {}
	Circle(int x, int y, int r) :
		x{ x }, y{ y }, radius{ r } {}
	void show();
};
void Circle::show() {
	cout << "¹ÝÁö¸§" << radius << "  @(" << x << ", " << y<< ")" << endl;
}
int main() {
	vector<Circle> objArray;
	for (int i = 0; i < 10; i++) {
		Circle obj{ rand() % 300, rand() % 300, rand() % 100 };
		objArray.push_back(obj);
	}
	for (Circle& c : objArray)
		c.show();
	return 0;
}
