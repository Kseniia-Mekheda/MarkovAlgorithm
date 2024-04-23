#include "pch.h"
#include "CppUnitTest.h"
#include "../MarkovAlgorithm/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MarkovTest
{
	TEST_CLASS(MarkovTest)
	{
	public:
		
		TEST_METHOD(AddRuleTest)
		{
			MarkovAlgorithm M;
			Assert::AreEqual(0, M.quantityOfRules());

			M.addRule(String("as"), String("Ss"));
			Assert::AreEqual(1, M.quantityOfRules());
		}
		TEST_METHOD(SwapTest)
		{
			String S("abba");
			S.swapByIndex(0, 2);
			const char* expected = "bbaa";
			Assert::AreEqual(expected, S.getString());
		}

		TEST_METHOD(ResizeTest)
		{
			String S("abba");
			S.resizeString(10);
			Assert::AreEqual(14, S.getSize());
		}

		TEST_METHOD(AlgorTest)
		{
			MarkovAlgorithm MA;
			MA.addRule(String("ab"), String("ba"));
			string expression = "ab";
			const char* array = expression.c_str();
			String in(array);
			string result = "ba";
			const char* arr = result.c_str();
			String C = MA.applyRule(in);
			Assert::AreEqual(arr, in.getString());
		}
	};
}
