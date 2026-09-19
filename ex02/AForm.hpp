#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class AForm
{
public:
	AForm();
	AForm(const std::string& name, int gradeToSign, int gradeToExecute);
	AForm(const AForm& other);
	AForm& operator=(const AForm& rhs);
	virtual ~AForm();

	const std::string& getName() const;
	bool isSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;

	void beSigned(const Bureaucrat& bureaucrat);
	void execute(const Bureaucrat& executor) const;
	virtual void executeAction() const = 0;

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

	class FormNotSignedException : public std::exception
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

std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif
