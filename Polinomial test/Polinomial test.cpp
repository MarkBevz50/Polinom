
#include "pch.h"
#include "CppUnitTest.h"
#include "..\PolyTools\Polinomial.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PolinomialTests
{
	TEST_CLASS(PolinomialTests)
	{
	public:

		TEST_METHOD(TestAreEqual)
		{
			double a[] = { -99.,1.,2.,1. };
			const int n = sizeof a / sizeof a[0];
			double b[] = { -99.,1.,2.,1. };
			const int m = sizeof b / sizeof b[0];
			Polynomial A = CreatePoly(a, n);
			Polynomial B = CreatePoly(b, m);
			Assert::IsTrue(AreEqual(A, B));

			double c[] = { -99.,1.,2.,1.,5.,0.,-4. };
			const int k = sizeof c / sizeof c[0];
			Polynomial C = CreatePoly(c, k);
			Assert::IsFalse(AreEqual(A, C));

			double d[] = { 75.,0.,-2.,-1.,0.,0.,4.,0.,1. };
			const int l = sizeof d / sizeof d[0];
			Polynomial D = CreatePoly(d, l);
			Assert::IsFalse(AreEqual(A, D));
			RemovePoly(A); RemovePoly(B); RemovePoly(C); RemovePoly(D);
		}
		TEST_METHOD(TestAdd)
		{
			double a[] = { -99.,1.,2.,1. };
			const int n = sizeof a / sizeof a[0];
			double b[] = { 75.,0.,-2.,-1.,0.,0.,4.,0.,1. };
			const int m = sizeof b / sizeof b[0];
			Polynomial A = CreatePoly(a, n);
			Polynomial B = CreatePoly(b, m);
			Polynomial C = AddPoly(A, B);

			double s[] = { -24.,1.,0.,0.,0.,0.,4.,0.,1. };
			Polynomial S = CreatePoly(s, sizeof s / sizeof s[0]);
			Assert::IsTrue(AreEqual(C, S));
			RemovePoly(A); RemovePoly(B); RemovePoly(C); RemovePoly(S);
		}
		TEST_METHOD(TestAddAlternative)
		{
			// альтернативний спосіб перевірки результатів додавання - 
			//  використати відомі коефіцієнти і степені
			double odd[] = { 1,0,3,0,5,0,7 };
			double even[] = { 0,2,0,4,0,6 };
			Polynomial A = CreatePoly(odd, sizeof odd / sizeof odd[0]);
			Polynomial B = CreatePoly(even, sizeof even / sizeof even[0]);
			Polynomial C = AddPoly(A, B);
			// odd + even = { 1,2,3,4,5,6,7 }
			Polynomial curr = C;
			for (int i = 1; i <= 7; ++i, curr = curr->next)
			{
				Assert::AreEqual((double)i, curr->coef);
				Assert::AreEqual(i - 1, curr->power);
			}
			RemovePoly(A); RemovePoly(B); RemovePoly(C);

			double high[] = { 0,0,0,0,0,0,0,0,0,0,5 };
			const int k = sizeof high / sizeof high[0];
			A = CreatePoly(high, k);
			double low[] = { -5 };
			B = CreatePoly(low, 1);
			C = AddPoly(A, B);
			Assert::AreEqual(-5.0, C->coef); Assert::AreEqual(0, C->power);
			Assert::AreEqual(5.0, C->next->coef); Assert::AreEqual(k - 1, C->next->power);
			RemovePoly(A); RemovePoly(B); RemovePoly(C);
		}
		TEST_METHOD(TestAddZero)
		{
			double pos[] = { 1.,2.,3.,4.,5. };
			double neg[] = { -1.,-2.,-3.,-4.,-5. };
			Polynomial A = CreatePoly(pos, 5);
			Polynomial B = CreatePoly(neg, 5);
			Assert::IsNull(AddPoly(A, B));
			RemovePoly(A); RemovePoly(B);
		}
		TEST_METHOD(TestCalcValue)
		{
			double a[] = { -16.,0.,0.,0.,1. };
			Polynomial A = CreatePoly(a, 5);
			Assert::AreEqual(0.0, CalcValue(A, 2.0));
			Assert::AreEqual(0.0, CalcValue(A, -2.0));
			Assert::AreEqual(-16.0, CalcValue(A, 0.0));
			Assert::AreEqual(-15.0, CalcValue(A, 1.0));
			RemovePoly(A);
		}
		TEST_METHOD(TestDegree)
		{
			double a[] = { -16.,0.,0.,0.,1. };
			Polynomial A = CreatePoly(a, 5);
			Assert::AreEqual(4, Degree(A));
			RemovePoly(A);
			double high[] = { 0,0,0,0,0,0,0,0,0,0,5 };
			const int k = sizeof high / sizeof high[0];
			A = CreatePoly(high, k);
			Assert::AreEqual(k - 1, Degree(A));
			RemovePoly(A);
			double low[] = { -5 };
			A = CreatePoly(low, 1);
			Assert::AreEqual(0, Degree(A));
			RemovePoly(A);
		}
		TEST_METHOD(TestMultPoly)
		{
			// Створюємо поліном A = 2x^2 + 1
			double aCoefficients[] = { 1, 0, 2 };
			Polynomial A = CreatePoly(aCoefficients, sizeof(aCoefficients) / sizeof(aCoefficients[0]));
			// Створюємо поліном B = x^2 + 3
			double bCoefficients[] = { 3, 0, 1 };
			Polynomial B = CreatePoly(bCoefficients, sizeof(bCoefficients) / sizeof(bCoefficients[0]));
			// Очікуваний результат: 2x^4 + 7x^2 + 3
			double expectedCoefficients[] = { 3, 0, 7, 0, 2 };
			Polynomial expectedResult = CreatePoly(expectedCoefficients, sizeof(expectedCoefficients) / sizeof(expectedCoefficients[0]));
			// Викликаємо функцію, яку тестуємо
			Polynomial result = MultPoly(A, B);
			// Перевірка кожного коефіцієнта та ступеня в результуючому поліномі
			for (int i = 0; i < sizeof(expectedCoefficients) / sizeof(expectedCoefficients[0]); ++i)
			{
				Assert::AreEqual(expectedCoefficients[i], result->coef, L"Unexpected coefficient value");
				Assert::AreEqual(i, result->power, L"Unexpected power value");
				result = result->next;
			}
			// Переконуємося, що обидва полінома завершились одночасно
			Assert::IsNull(result);
			// Звільняємо пам'ять
			RemovePoly(A);
			RemovePoly(B);
			RemovePoly(expectedResult);
		}
		TEST_METHOD(Test_Integral)
		{
			double a[] = { -99.,1.,2.,1. };
			const int n = sizeof a / sizeof a[0];
			double b[] = { 0.,-99,1 / 2.,2 / 3.,1 / 4. };
			const int m = sizeof b / sizeof b[0];
			Polynomial A = CreatePoly(a, n);
			Polynomial B = CreatePoly(b, m);
			Polynomial C = Integral(A);
			Assert::IsTrue(AreEqual(C, B));
			/*remove(A);
			remove(B);
			remove(C);*/
		}
		TEST_METHOD(Test_IntegralPoint)
		{
			double a[] = { -99.,1.,2.,1. };
			const int n = sizeof a / sizeof a[0];
			double b[] = { 1195 / 12.,-99.,1 / 2.,2 / 3.,1 / 4. };
			const int m = sizeof b / sizeof b[0];
			Polynomial A = CreatePoly(a, n);
			Polynomial B = CreatePoly(b, m);
			Polynomial C = IntegralPoint(A, 1, 2);
			Assert::IsTrue(AreEqual(C, B));
			/*remove(A);
			remove(B);
			remove(C);*/
		}
		TEST_METHOD(TestMultByC)
		{
			double coefs[] = { 1.0, 0.0, 0.0,0.0,0.0,24.0,0.0,8.0 }; // Поліном A = 1 + 24x^5 + 8x^7
			Polynomial A = CreatePoly(coefs, sizeof coefs / sizeof coefs[0]);
			double c = 6.0;
			Polynomial result = MultByC(A, c); // A * 6 = 6 + 144x^5 + 48x^7 результат правельний, проте тест не проходить
			double expectedCoefs[] = { 6.0, 0.0, 0.0,0.0,0.0,144.0,0.0,48.0 };
			Polynomial expectedResult = CreatePoly(expectedCoefs, sizeof expectedCoefs / sizeof expectedCoefs[0]);
			// Перевірка кожного коефіцієнта та ступеня в результуючому поліномі
			for (int i = 0; i < sizeof expectedCoefs / sizeof expectedCoefs[0]; ++i)
			{
				Assert::AreEqual(expectedCoefs[i], result->coef, L"Unexpected coefficient value");
				Assert::AreEqual(i, result->power, L"Unexpected power value");
				result = result->next;
			}
			RemovePoly(A);
			RemovePoly(result);
			RemovePoly(expectedResult);
		}
		TEST_METHOD(TestPolynomialPower)
		{
			double a[] = { 0.0, 2.0, 2.0, 4.0 }; // 2x + 2x^2 + 4x^3
			const int n = sizeof a / sizeof a[0];
			Polynomial poly = CreatePoly(a, n);

			Polynomial result = ReversePoly(PowerElem(poly, 3));

			double expected[] = { 0.0, 0.0, 4.0, 0.0, 4.0, 0.0, 16.0 };  //4x^2 + 4x^4 + 16x^6 так і виконується, проте тест не проходить
			Polynomial expectedPoly = CreatePoly(expected, sizeof expected / sizeof expected[0]);

			Assert::IsTrue(AreEqual(result, expectedPoly));

			RemovePoly(poly);
			RemovePoly(expectedPoly);
		}
	};
}