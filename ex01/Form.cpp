#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form()
	: _name("DefaultForm"), _isSigned(false), _gradeToSign(LOWEST_GRADE), _gradeToExecute(LOWEST_GRADE)
{
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (gradeToSign < HIGHEST_GRADE || gradeToExecute < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (gradeToSign > LOWEST_GRADE || gradeToExecute > LOWEST_GRADE)
		throw GradeTooLowException();
}

Form::Form(const Form& other)
	: _name(other._name),
	  _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign),
	  _gradeToExecute(other._gradeToExecute)
{
}

Form& Form::operator=(const Form& rhs)
{
	if (this != &rhs)
	{
		_isSigned = rhs._isSigned;
	}
	return *this;
}

Form::~Form()
{
}

const std::string& Form::getName() const
{
	return _name;
}

bool Form::isSigned() const
{
	return _isSigned;
}

int Form::getGradeToSign() const
{
	return _gradeToSign;
}

int Form::getGradeToExecute() const
{
	return _gradeToExecute;
}

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "Form grade is too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Form grade is too low";
}

std::ostream& operator<<(std::ostream& os, const Form& form)
{
	os << "Form " << form.getName()
	   << " [signed: " << (form.isSigned() ? "yes" : "no")
	   << ", grade to sign: " << form.getGradeToSign()
	   << ", grade to execute: " << form.getGradeToExecute() << "]";
	return os;
}
