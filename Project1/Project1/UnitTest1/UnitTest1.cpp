#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Source.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(StudentTests)
    {
    public:

        TEST_METHOD(TestBinarySearchStudent)
        {

            const int N = 3;
            Student students[N] = { {"Dio", 1, KN, 85, 90, 88},
                                   {"Smith", 2, ME, 75, 80, 78},
                                   {"Johnatan", 3, IN, 90, 95, 92} };


            Assert::IsTrue(BinarySearch(students, N, "Dio", 1, 88));


            Assert::IsFalse(BinarySearch(students, N, "Smith", 2, 85));


            Assert::IsFalse(BinarySearch(students, N, "Johnatan", 3, 94));
        }
    };
}

