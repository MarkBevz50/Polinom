#pragma once
#include <iostream>
struct Polynode;
using Polynomial = Polynode*;

struct Polynode
{
	double coef;
	int power;
	Polynomial next;
	Polynode(double c, int p, Polynomial n = nullptr) : coef(c), power(p), next(n) {};

};
	//Створює список-поліном за масивом коефіцієнтів, що починається з вільного члена
	Polynomial CreatePoly(double* a, int n);
	double CalcValue(Polynomial p, double x);
	Polynomial Add(Polynomial a, Polynomial b);
	std::ostream& operator << (std::ostream& os, Polynomial p);
	
	bool AreEqual(Polynomial A, Polynomial B);

