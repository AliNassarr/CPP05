#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class Form
{
public:
	Form();
	Form(const std::string& name, int gradeToSign, int gradeToExecute);
	Form(const Form& other);
	Form& operator=(const Form& rhs);
	~Form();

	const std::string& getName() const;
	bool isSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;

	void beSigned(const Bureaucrat& bureaucrat);

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

private:
	static const int HIGHEST_GRADE = 1;
	static const int LOWEST_GRADE = 150;

	const std::string _name;
	bool _isSigned;
	const int _gradeToSign;
	const int _gradeToExecute;
};

std::ostream& operator<<(std::ostream& os, const Form& form);

#endif
