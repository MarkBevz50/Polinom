#include "pch.h"
#include "Polinomial.h"
#include <iomanip>

Polynomial ReadPoly(std::istream& is)
{
    Polynomial poly = nullptr;
    while (true)
    {
        double coef;
        int power;

        std::cout << "Enter the coefficient(or 0 to stop)" <<  ' \n';
        is >> coef;
        if (coef == 0)
        {
            break;
        }
        std::cout << "Enter power: " << ' \n';
        is >> power;

        Polynomial newNode = new PolyNode(coef, power, poly);
            poly = newNode;


            
    }
    return poly;
}

Polynomial CreatePoly(double* a, int n)
{
    PolyNode phantom(0, 0);
    Polynomial curr = &phantom;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] != 0.0)
        {
            curr->next = new PolyNode(a[i], i);
            curr = curr->next;
        }
    }
    return phantom.next;
}

void RemovePoly(Polynomial& p)
{
    while (p != nullptr)
    {
        Polynomial victim = p;
        p = p->next;
        delete victim;
    }
}

Polynomial AddPoly(Polynomial a, Polynomial b)
{
    PolyNode phantom(0, 0);
    Polynomial curr = &phantom;
    while (a != nullptr && b != nullptr)
    {
        if (a->power == b->power)
        {
            double s = a->coef + b->coef;
            if (s != 0.0)
            {
                curr->next = new PolyNode(s, a->power);
                curr = curr->next;
            }
            a = a->next; b = b->next;
        }
        else if (a->power < b->power)
        {
            curr->next = new PolyNode(a->coef, a->power);
            curr = curr->next;
            a = a->next;
        }
        else
        {
            curr->next = new PolyNode(b->coef, b->power);
            curr = curr->next;
            b = b->next;
        }
    }
    while (a != nullptr)
    {
        curr->next = new PolyNode(a->coef, a->power);
        curr = curr->next;
        a = a->next;
    }
    while (b != nullptr)
    {
        curr->next = new PolyNode(b->coef, b->power);
        curr = curr->next;
        b = b->next;
    }
    return phantom.next;
}

Polynomial MultByC(Polynomial a, double c)
{
    Polynomial result = nullptr;
    while (a != nullptr) {
        double prod = a->coef * c;
        result = new PolyNode(prod, a->power, result);
        a = a->next;
    }
    return result;
}

Polynomial MultPoly(Polynomial a, Polynomial b)
{
    Polynomial result = nullptr;
    Polynomial aCurrent = a;

    while (aCurrent != nullptr)
    {
        Polynomial bCurrent = b;

        while (bCurrent != nullptr)
        {
            double prodpow = aCurrent->power + bCurrent->power;
            double coefprod = aCurrent->coef * bCurrent->coef;

            // Додати до існуючого вузла, якщо ступінь вже існує
            Polynomial existingNode = FindNodeWithPower(result, prodpow);
            if (existingNode != nullptr)
            {
                existingNode->coef += coefprod;
            }
            else
            {
                // Додати новий вузол
                result = new PolyNode(coefprod, prodpow, result);
            }

            bCurrent = bCurrent->next;
        }

        aCurrent = aCurrent->next;
    }
    result = SortByPower(result);
    
    return result;
}


bool AreEqual(Polynomial A, Polynomial B)
{
    while (A != nullptr && B != nullptr && A->coef == B->coef && A->power == B->power)
    {
        A = A->next;
        B = B->next;
    }
    return A == B;
}

double CalcValue(Polynomial P, double x)
{
    double res = 0.0;
    double p = 1.0; // ������ x
    int i = 0;
    while (P != nullptr)
    {
        while (i < P->power)
        {
            p *= x;
            ++i;
        }
        res += P->coef * p;
        P = P->next;
    }
    return res;
}

int Degree(Polynomial p)
{
    while (p->next != nullptr) p = p->next;
    return p->power;
}

Polynomial Derivative(Polynomial p)
{
    if (p->power == 0) p = p->next;
    PolyNode phantom(0., 0);
    Polynomial curr = &phantom;
    while (p != nullptr)
    {
        curr->next = new PolyNode(p->coef * p->power, p->power - 1);
        curr = curr->next;
        p = p->next;
    }
    return phantom.next;
}



std::ostream& operator<<(std::ostream& os, Polynomial p)
{
    while (p != nullptr)
    {
        os << std::showpos << p->coef << "x^" << std::noshowpos << p->power << ' ';
        p = p->next;
    }
    return os;
}

Polynomial FindNodeWithPower(Polynomial poly, double TargetPower)
{
    while (poly != nullptr)
    {
        if (poly->power == TargetPower)
        {
            return poly;
        }
        poly = poly->next;
    }
    return nullptr;
}


Polynomial SortByPower(Polynomial poly)
{
    if (poly == nullptr || poly->next == nullptr)
    {
        return poly;
    }

    bool swaped;
    Polynomial start;
    Polynomial current;
    Polynomial origin = poly;

    do {
        start = poly;
        swaped = false;
        current = start;
        while (current->next != nullptr)
        {
            if (current->power < current->next->power || current->power == current->next->power && current->power < current->next->power)
            {
                Swap(current, current->next);
                swaped = true;
            }
            current = current->next;
        }

    } while (swaped);
    return start;
}



void Swap(PolyNode*& a, PolyNode*& b)
{
    PolyNode* temp = a;
    a = b;
    b = temp;
}

Polynomial PolyNode::operator+(Polynomial other)
{
    return AddPoly(this, other);
}