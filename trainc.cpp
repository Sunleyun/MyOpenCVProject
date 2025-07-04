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

Circle::Circle(double r): radius(r) {}

double Circle::area() const {
	return 3.14 * radius * radius;
}

Rectangle::Rectangle(double _w, double _h): w(_w), h(_h) {}

double Rectangle::area() const {
	return w * h;
}

void Main_C() {
	Circle c1(4);
	cout << c1.area() << endl;
	Rectangle r1(4, 5);
	cout << r1.area() << endl;
}