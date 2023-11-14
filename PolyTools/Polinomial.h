#include <iostream>
#include "pch.h"
struct PolyNode;
using Polynomial = PolyNode*;
struct PolyNode
{
	double coef;
	int power;
	Polynomial next;
	PolyNode(double c, int p, Polynomial n = nullptr) :coef(c), power(p), next(n) {}
	Polynomial operator+(Polynomial other);
};

Polynomial ReadPoly(std::istream& is);


Polynomial CreatePoly(double* a, int n);
void RemovePoly(Polynomial& p);

Polynomial AddPoly(Polynomial a, Polynomial b);

Polynomial MultByC(Polynomial a, double c);
Polynomial MultPoly(Polynomial a, Polynomial b);

bool AreEqual(Polynomial A, Polynomial B);

double CalcValue(Polynomial P, double x);

int Degree(Polynomial p);

Polynomial Derivative(Polynomial p);

Polynomial Integral(Polynomial p, double x_0, double y_0);

std::ostream& operator<<(std::ostream& os, Polynomial p);
Polynomial FindNodeWithPower(Polynomial poly, double TargetPower); //Додаткова функція, пошук вузла який зберішає бажаний степінь
Polynomial SortByPower(Polynomial poly); //Помилка(Вічний цикл)
void Swap(PolyNode*& a, PolyNode*& b);
