#include "pch.h"
#include "CppUnitTest.h"
#include "..\PolyTools\Polinomial.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Polinomialtest
{
	TEST_CLASS(Polinomialtest)
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
			double c[] = { -99.,1.,2.,1.,5,4,2 };
			const int k = sizeof c / sizeof c[0];
			Polynomial C = CreatePoly(c, k);
			Assert::IsFalse(AreEqual(A, C));
		}
		TEST_METHOD(Test_Add)
		{
			





		}
	};
}
