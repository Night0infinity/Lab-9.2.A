#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab 9.2/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest91A
{
	TEST_CLASS(UnitTest91A)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			string surname = "v";
			Student* p = new Student[2];
			p[0].kurs = 2;
			p[0].prizv = "w";
			p[0].fizika = 5;
			p[0].matematika = 5;
			p[0].informatika = 5;

			p[1].kurs = 1;
			p[1].prizv = "v";
			p[1].fizika = 4;
			p[1].matematika = 4;
			p[1].informatika = 4;
			Sort(p, 2);
			Assert::AreEqual(p[0].prizv, surname);
			Assert::AreEqual(p[0].fizika, 4.);
			Assert::AreEqual(p[0].matematika, 4.);
			Assert::AreEqual(p[0].informatika, 4.);
		}
	};
}
