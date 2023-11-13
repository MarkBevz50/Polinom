	#include <iostream>
#include "..\PolyTools\Polinomial.h"
        using std::cout;
int main()
{
        double a[] = { -99.,1.,2.,1. };
        const int n = sizeof a / sizeof a[0];
        double b[] = { 75.,0.,-2.,-1.,0.,0.,4.,0.,1. };
        const int m = sizeof b / sizeof b[0];
        Polynomial P = CreatePoly(a, n);
        std::cout << "P_3(x) = " << P << '\n';
        Polynomial P2 = AddPoly(P, P);
        std::cout << "P2_3(x) = " << P2 << '\n';
        Polynomial R = CreatePoly(b, m);
        std::cout << "R_8(x) = " << R << '\n';
        Polynomial C = AddPoly(P, R);
        std::cout << "C_8(x) = " << C << '\n';
        std::cout << "Are equal: " << std::boolalpha << AreEqual(P, P)
            << "\nAre equal: " << AreEqual(P, P2) << '\n';
        Polynomial D = *P + R;
        std::cout << "D_8(x) = " << D << '\n';
        std::cout << "The function and the operator act equally: " << AreEqual(C, D) << '\n';
        Polynomial V = Derivative(C);
        std::cout << "C_8'(x) = " << V << '\n';
        RemovePoly(V);
        RemovePoly(P);
        RemovePoly(P2);
        RemovePoly(R);
        RemovePoly(C);
        RemovePoly(D);
        return 0;
    }


