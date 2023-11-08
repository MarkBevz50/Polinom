#include <iostream>
#include "..\PolyTools\Polinomial.h"

int main()
{
	double a[] = { -99.,1.,2.,1. };
	const int n = sizeof a / sizeof a[0];
	Polynomial P = CreatePoly(a, n);
	std::cout << "p_3"(X) = << P << '\n';
	return 0;



}