#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm()
	: _name("DefaultForm"), _isSigned(false), _gradeToSign(LOWEST_GRADE), _gradeToExecute(LOWEST_GRADE)
{
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (gradeToSign < HIGHEST_GRADE || gradeToExecute < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (gradeToSign > LOWEST_GRADE || gradeToExecute > LOWEST_GRADE)
		throw GradeTooLowException();
}

AForm::AForm(const AForm& other)
	: _name(other._name),
	  _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign),
	  _gradeToExecute(other._gradeToExecute)
{
}

AForm& AForm::operator=(const AForm& rhs)
{
	if (this != &rhs)
	{
		_isSigned = rhs._isSigned;
	}
	return *this;
}

AForm::~AForm()
{
}

const std::string& AForm::getName() const
{
	return _name;
}

bool AForm::isSigned() const
{
	return _isSigned;
}

int AForm::getGradeToSign() const
{
	return _gradeToSign;
}

int AForm::getGradeToExecute() const
{
	return _gradeToExecute;
}

void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const
{
	if (!_isSigned)
		throw FormNotSignedException();
	if (executor.getGrade() > _gradeToExecute)
		throw GradeTooLowException();
	executeAction();
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "Form grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "Form grade is too low";
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return "Form is not signed";
}

std::ostream& operator<<(std::ostream& os, const AForm& form)
{
	os << "Form " << form.getName()
	   << " [signed: " << (form.isSigned() ? "yes" : "no")
	   << ", grade to sign: " << form.getGradeToSign()
	   << ", grade to execute: " << form.getGradeToExecute() << "]";
	return os;
}
