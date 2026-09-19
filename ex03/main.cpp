#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"
#include <iostream>

int main()
{
	Intern someRandomIntern;
	Bureaucrat boss("Alnassar", 1);

	std::cout << "=== Intern Creates Valid Forms ===" << std::endl;
	AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	if (rrf)
	{
		boss.signForm(*rrf);
		boss.executeForm(*rrf);
		delete rrf;
	}

	std::cout << "\n=== Intern Creates Shrubbery Form ===" << std::endl;
	AForm* scf = someRandomIntern.makeForm("shrubbery creation", "courtyard");
	if (scf)
	{
		boss.signForm(*scf);
		boss.executeForm(*scf);
		delete scf;
	}

	std::cout << "\n=== Intern Creates Presidential Pardon Form ===" << std::endl;
	AForm* ppf = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
	if (ppf)
	{
		boss.signForm(*ppf);
		boss.executeForm(*ppf);
		delete ppf;
	}

	std::cout << "\n=== Intern Tries Unknown Form ===" << std::endl;
	AForm* unknown = someRandomIntern.makeForm("coffee request", "Boss");
	if (unknown)
	{
		delete unknown;
	}

	return 0;
}
