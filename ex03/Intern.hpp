#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include "AForm.hpp"

class Intern
{
public:
	Intern();
	Intern(const Intern& other);
	Intern& operator=(const Intern& rhs);
	~Intern();

	AForm* makeForm(const std::string& formName, const std::string& target) const;

private:
	typedef AForm* (Intern::*FormCreator)(const std::string& target) const;

	struct FormEntry
	{
		const char* name;
		FormCreator create;
	};

	AForm* _createShrubbery(const std::string& target) const;
	AForm* _createRobotomy(const std::string& target) const;
	AForm* _createPresidential(const std::string& target) const;
};

#endif
