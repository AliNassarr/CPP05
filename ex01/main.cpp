#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Testing Successful Form Signing ===" << std::endl;
	try
	{
		Bureaucrat boss("Alnassar", 30);
		Form permit("BuildingPermit", 45, 20);

		std::cout << boss << std::endl;
		std::cout << permit << std::endl;

		boss.signForm(permit);
		std::cout << permit << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Unexpected exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Testing Form Signing with Insufficient Grade ===" << std::endl;
	try
	{
		Bureaucrat rookie("Rookie", 120);
		Form secretDoc("ConfidentialReport", 50, 25);

		std::cout << rookie << std::endl;
		std::cout << secretDoc << std::endl;

		rookie.signForm(secretDoc);
		std::cout << secretDoc << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Unexpected exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Testing Invalid Form Construction ===" << std::endl;
	try
	{
		Form impossible("ImpossibleForm", 0, 50);
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught expected exception (grade 0):   " << e.what() << std::endl;
	}

	try
	{
		Form impossible2("ImpossibleForm2", 50, 151);
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught expected exception (grade 151): " << e.what() << std::endl;
	}

	return 0;
}
