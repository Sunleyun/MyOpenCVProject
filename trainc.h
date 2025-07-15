#ifndef TRAINC_H
#define TRAINC_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstring>
#include <numeric>

struct TreeNode {
	int val;
	TreeNode* left, * right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
void inorderTraversal(TreeNode* root, std::vector<int>& result);

void swap_reference(int &a, int &b);
void swap_pointer(int *a, int *b);
void reverseArray(std::vector<int>& vec);
void test_shared_ptr();
void lambda_test(std::vector<int>& vec);
void Max_vector(std::vector<int>& vec, int& sum, std::vector<int>::iterator& max);

class Point {
public:
	Point() = default;
	Point(double, double);
	Point operator+(const Point&) const;
	double distance() const;
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

class String {
public:
	String(const char* s) : data(new char[strlen(s) + 1]) {
		strcpy(data, s);
	}
	String(String&& other) noexcept : data(other.data) {
		other.data = nullptr;
	}
	~String() { delete[] data; }
	const char* c_str() const { return data; }
private:
	char* data;
};

void Main_C();

#endif // TRAINCXX_H