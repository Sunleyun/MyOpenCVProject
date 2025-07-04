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
private:
	double x, y;
};

void Main_C();

#endif // TRAINCXX_H