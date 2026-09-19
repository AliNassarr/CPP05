#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Valid Bureaucrat Tests ===" << std::endl;
	try
	{
		Bureaucrat worker("Alnassar", 75);
		std::cout << worker << std::endl;

		worker.incrementGrade();
		std::cout << "After promotion: " << worker << std::endl;

		worker.decrementGrade();
		std::cout << "After demotion:  " << worker << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Unexpected error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Exception: Increment Beyond Grade 1 ===" << std::endl;
	try
	{
		Bureaucrat minister("Minister", 1);
		std::cout << minister << std::endl;
		std::cout << "Attempting promotion beyond grade 1..." << std::endl;
		minister.incrementGrade();
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught expected exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Exception: Decrement Beyond Grade 150 ===" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 150);
		std::cout << intern << std::endl;
		std::cout << "Attempting demotion beyond grade 150..." << std::endl;
		intern.decrementGrade();
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught expected exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Exception: Construct with Invalid Grades ===" << std::endl;
	try
	{
		Bureaucrat god("God", 0);
	}
	catch (const std::exception& e)
	{
		std::cout << "Construct grade 0 caught:   " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat peasant("Peasant", 151);
	}
	catch (const std::exception& e)
	{
		std::cout << "Construct grade 151 caught: " << e.what() << std::endl;
	}

	return 0;
}
