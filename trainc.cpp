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

void Main_C() {
	int n1 = 3, n2 = 4;
	swap_reference(n1, n2);
	cout << n1 << " " << n2 << endl;
	swap_pointer(&n1, &n2);
	cout << n1 << " " << n2 << endl;
}