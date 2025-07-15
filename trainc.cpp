#include "trainc.h"
using namespace std;

void inorderTraversal(TreeNode* root, std::vector<int>& result) {
	if (root == nullptr) return;
	inorderTraversal(root->left, result);
	result.push_back(root->val);
	inorderTraversal(root->right, result);
}

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

void test_shared_ptr() {
	shared_ptr<int> ptr1 = make_shared<int>();
	cout << ptr1.use_count() << endl;
	shared_ptr<int> ptr2 = ptr1;
	cout << ptr1.use_count() << " " << ptr2.use_count() << endl;
}

void lambda_test(vector<int>& vec) {
	sort(vec.begin(), vec.end(), [](int a, int b) {
		return abs(a) < abs(b);
	});
	for (int i : vec) cout << i << " ";
}

void Max_vector(vector<int>& vec, int& sum, vector<int>::iterator& max) {
	sum = std::accumulate(vec.begin(), vec.end(), 0);
	max = std::max_element(vec.begin(), vec.end());
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
	vector<int> result;
	TreeNode* root = new TreeNode(1);
	root->right = new TreeNode(2);
	root->right->left = new TreeNode(3);
	inorderTraversal(root, result);
	for (int val : result) cout << val << " ";
}