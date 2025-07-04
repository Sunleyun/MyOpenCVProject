#ifndef TRAINC_H
#define TRAINC_H
#include <iostream>
using namespace std;

void swap_reference(int &a, int &b);
void swap_pointer(int *a, int *b);

class Point {
public:
	Point() = default;
	Point(double, double);
	Point operator+(const Point&) const;
	void show();
	~Point() = default;
private:
	double x, y;
};

class Shape {
public:
	virtual double area() const = 0;
	virtual ~Shape() {}
};

class Circle : public Shape {
public:
	Circle(double);
	double area() const override;
private:
	double radius;
};

class Rectangle : public Shape {
public:
	Rectangle(double, double);
	double area() const override;
private:
	double w, h;
};

void Main_C();

#endif // TRAINCXX_H