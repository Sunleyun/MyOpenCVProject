#include "trainc.h"

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

Point::Point(double x_, double y_): x(x_), y(y_) {}

Point Point::operator+(const Point& other) const {
	return Point(x + other.x, y + other.y);
}

void Point::show() {
	cout << x << " " << y << endl;
}

void Main_C() {
	Point p1(2, 5);
	Point p2(3, 6);
	p1 = p1 + p2;
	p1.show();
}