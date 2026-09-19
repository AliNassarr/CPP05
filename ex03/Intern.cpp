#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

Intern::Intern()
{
}

Intern::Intern(const Intern& other)
{
	(void)other;
}

Intern& Intern::operator=(const Intern& rhs)
{
	(void)rhs;
	return *this;
}

Intern::~Intern()
{
}

AForm* Intern::_createShrubbery(const std::string& target) const
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::_createRobotomy(const std::string& target) const
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::_createPresidential(const std::string& target) const
{
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
	const FormEntry registry[] = {
		{ "shrubbery creation", &Intern::_createShrubbery },
		{ "robotomy request", &Intern::_createRobotomy },
		{ "presidential pardon", &Intern::_createPresidential }
	};

	const int totalForms = sizeof(registry) / sizeof(registry[0]);
	for (int i = 0; i < totalForms; ++i)
	{
		if (formName == registry[i].name)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (this->*(registry[i].create))(target);
		}
	}

	std::cout << "Intern cannot create " << formName << " because the form type is unknown." << std::endl;
	return NULL;
}
