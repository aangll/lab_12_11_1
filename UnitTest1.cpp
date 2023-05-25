#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12_11/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            TelephoneDirectory directory;
            directory.count = 3;
            directory.subscribers = new Subscriber[directory.count];

            directory.subscribers[0].name = "John Doe";
            directory.subscribers[0].phoneNumber = "123456789";

            directory.subscribers[1].name = "Jane Smith";
            directory.subscribers[1].phoneNumber = "987654321";

            directory.subscribers[2].name = "Alice Johnson";
            directory.subscribers[2].phoneNumber = "555555555";

            // Redirect cout to a stringstream to capture the output
            std::stringstream output;
            std::streambuf* oldCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(output.rdbuf());

            // Call the function to be tested
            printTelephoneDirectory(directory);

            // Restore the original cout buffer
            std::cout.rdbuf(oldCoutBuffer);

            // Verify the expected output
            std::string expectedOutput =
                "Telephone Directory:\n"
                "Subscriber 1:\n"
                "Name: John Doe\n"
                "Phone Number: 123456789\n"
                "Subscriber 2:\n"
                "Name: Jane Smith\n"
                "Phone Number: 987654321\n"
                "Subscriber 3:\n"
                "Name: Alice Johnson\n"
                "Phone Number: 555555555\n";
           Assert::AreEqual(output.str(), expectedOutput);
		}
	};
}
