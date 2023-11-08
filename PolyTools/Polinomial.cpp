#include "pch.h"
#include "Polinomial.h"

Polynomial Polynode::CreatePoly(double* a, int n)
{
    Polynode phantom(0, 0);
    Polynomial curr = &phantom;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] != 0.0)
        {
            curr->next = new Polynode(a[i], i);
            curr = curr->next;
        }
    }
    return phantom.next;
}
Polynomial Add(Polynomial a, Polynomial b)
{
    Polynode phantom(0, 0);
    Polynomial curr = &phantom;
    while (a != nullptr && b != nullptr)
    {
        if (a->power == b->power)
        {
            double s = a->coef + b->coef;
            if (s != 0.0)
            {
                curr->next = new Polynode(s, a->power);
                curr = curr->next;
            }
            a = a->next; b = b->next;
        }
        else if (a->power < b->power)
        {
            curr->next = new Polynode(a->coef, a->power);
            curr = curr->next;
            a = a->next;

        }
    
        else
        {
            curr->next = new Polynode(b->coef, b->power);
            curr = curr->next;
            b = b->next;
        }

 }
    return phantom.next;
}
std::ostream& operator << (std::ostream& os, Polynomial p)
{
    while (p != nullptr)
    {
        os << p->coef << "x^" << p->power << ' ';

    }

}