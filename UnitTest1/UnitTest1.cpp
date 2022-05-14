#include "pch.h"
#include "CppUnitTest.h"
#include "../5.4/5.4.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char fname[100]{ 'U','n','i','t','T','e','s','t' };
			CreateFileToUnit();
			Print(fname);
		}
	};
}
