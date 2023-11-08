#include <iostream>
#include "..\PolyTools\Polinomial.h"

int main()
{
	double a[] = { -99.,1.,2.,1. };
	const int n = sizeof a / sizeof a[0];
	double b[] = { 75,0,-2,-1,0,0,4,2 };
	const int m = sizeof b / sizeof b[0];
	Polynomial A = CreatePoly(a, n);
	cout << "A = " << A;
	Polynomial B = CreatePoly(b, m);
	cout << '\n' << "B = " << B;
	Polynomial C = Add(A, B);
	cout << '\n' << "C = " << C;
	cout << "\nAre equal: " << areEqual(A, A) << "\nAre equal: " << areEqual(A, C);


}