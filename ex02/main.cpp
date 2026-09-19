#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Creating Bureaucrats ===" << std::endl;
	Bureaucrat president("Alnassar", 1);
	Bureaucrat manager("Manager", 40);
	Bureaucrat trainee("Trainee", 140);

	std::cout << president << std::endl;
	std::cout << manager << std::endl;
	std::cout << trainee << std::endl;

	std::cout << "\n=== Testing ShrubberyCreationForm ===" << std::endl;
	ShrubberyCreationForm shrub("garden");
	std::cout << shrub << std::endl;
	manager.executeForm(shrub); // Should fail: not signed
	trainee.signForm(shrub);
	manager.executeForm(shrub); // Should succeed

	std::cout << "\n=== Testing RobotomyRequestForm ===" << std::endl;
	RobotomyRequestForm robotomy("Bender");
	std::cout << robotomy << std::endl;
	manager.signForm(robotomy);
	manager.executeForm(robotomy);

	std::cout << "\n=== Testing PresidentialPardonForm ===" << std::endl;
	PresidentialPardonForm pardon("Ford Prefect");
	std::cout << pardon << std::endl;
	manager.signForm(pardon);   // Should fail: manager grade 40 > 25
	president.signForm(pardon); // Should succeed
	manager.executeForm(pardon); // Should fail: manager grade 40 > 5
	president.executeForm(pardon); // Should succeed

	return 0;
}
