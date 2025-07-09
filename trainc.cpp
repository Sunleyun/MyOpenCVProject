#include "trainc.h"
using namespace std;

void swap_reference(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void swap_pointer(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void reverseArray(vector<int>& vec) {
	reverse(vec.begin(), vec.end());
}

Point::Point(double x_, double y_): x(x_), y(y_) {}

Point Point::operator+(const Point& other) const {
	return Point(x + other.x, y + other.y);
}

double Point::distance() const {
	return sqrt(x * x + y * y);
}

void Point::show() {
	cout << x << " " << y << endl;
}

Circle::Circle(double r): radius(r) {}

double Circle::area() const {
	return 3.14 * radius * radius;
}

Rectangle::Rectangle(double _w, double _h): w(_w), h(_h) {}

double Rectangle::area() const {
	return w * h;
}

void Main_C() {
	vector<Point> vec = { {1, 1}, {2, 2}, {3, 3} };
	for (const auto& p : vec) {
		cout << p.distance() << " ";
	}
}