#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", 145, 137), _target("default_target")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), _target(other._target)
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& rhs)
{
	if (this != &rhs)
	{
		AForm::operator=(rhs);
		_target = rhs._target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::executeAction() const
{
	const std::string filename = _target + "_shrubbery";
	std::ofstream outFile(filename.c_str());
	if (!outFile.is_open())
		return;

	outFile << "               ,@@@@@@@,\n"
			<< "       ,,,.   ,@@@@@@/@@,  .oo888bbbbooo\n"
			<< "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o\n"
			<< "   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'\n"
			<< "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'\n"
			<< "   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'\n"
			<< "   `&%\\ ` /%&'    |.|        \\ '|8'\n"
			<< "       |o|        | |         | |\n"
			<< "       |.|        | |         | |\n"
			<< "    \\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/_"
			<< std::endl;

	outFile.close();
}
