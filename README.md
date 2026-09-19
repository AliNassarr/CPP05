This project has been created as part of the 42 curriculum by alnassar.

# C++ - Module 05: Repetition and Exceptions

## Description
**C++ Module 05** is an introduction to advanced Object-Oriented Programming in C++98, focusing on **Exception Handling**, **Abstract Classes**, **Subtype Polymorphism**, and **Design Patterns** within a bureaucratic office simulation.

The objective of this module is to transition away from C-style error codes (e.g. returning -1 or NULL) to standard C++ exception handling (`try`, `catch`, `throw`), while enforcing strict encapsulation, the Orthodox Canonical Form (OCF), and clean architectural design patterns such as the Template Method pattern and dispatch tables using pointers to member functions.

---

## Exercises Overview

### [Exercise 00: Mommy, when I grow up, I want to be a bureaucrat!](ex00/)
Introduces the `Bureaucrat` class, representing an administrative cog with:
- A constant name (`const std::string _name`).
- A grade ranging from **1 (highest possible)** to **150 (lowest possible)**.
- Boundary enforcement: Any invalid grade during construction, promotion (`incrementGrade()`), or demotion (`decrementGrade()`) throws either `Bureaucrat::GradeTooHighException` or `Bureaucrat::GradeTooLowException` inheriting from `std::exception`.
- Stream insertion operator (`operator<<`) formatting output as: `<name>, bureaucrat grade <grade>.`

### [Exercise 01: Form up, maggots!](ex01/)
Introduces the `Form` class to give bureaucrats documents to sign:
- Encapsulates private attributes: `const std::string _name`, `bool _isSigned`, `const int _gradeToSign`, and `const int _gradeToExecute`.
- `beSigned(const Bureaucrat&)`: Validates that the bureaucrat's grade is high enough (`grade <= _gradeToSign`) before setting the signed status.
- `Bureaucrat::signForm(Form&)`: Attempts to sign the form and reports the result:
  - Success: `<bureaucrat> signed <form>`
  - Failure: `<bureaucrat> couldn't sign <form> because <reason>`

### [Exercise 02: No, you need form 28B, not 28C...](ex02/)
Transforms `Form` into an abstract base class `AForm` with a pure virtual method `executeAction() const = 0`, implementing three concrete forms:
- **`ShrubberyCreationForm`** (Sign: 145, Exec: 137): Creates a `<target>_shrubbery` file in the working directory containing ASCII trees.
- **`RobotomyRequestForm`** (Sign: 72, Exec: 45): Emits drilling noises and reports 50% randomized success or failure.
- **`PresidentialPardonForm`** (Sign: 25, Exec: 5): Declares that the target has been pardoned by Zaphod Beeblebrox.
- **Template Method Pattern**: `AForm::execute(const Bureaucrat&)` handles all common validation (verifying the form is signed and the executor has sufficient grade) before invoking the derived class's `executeAction()`.
- `Bureaucrat::executeForm(const AForm&)`: Attempts execution and prints the appropriate status message.

### [Exercise 03: At least this beats coffee-making](ex03/)
Introduces the `Intern` class, capable of dynamically generating concrete forms via:
- `AForm* makeForm(const std::string& formName, const std::string& target) const;`
- **Zero `if/else if` chains**: Uses an internal dispatch table of structs pairing form names with **pointers to member functions**:
  ```cpp
  typedef AForm* (Intern::*FormCreator)(const std::string& target) const;
  ```
- Gracefully handles unknown form requests by printing an explicit error message and returning `NULL`.

---

## Instructions

### Compilation
Each exercise is compiled independently using its own `Makefile` with the strict C++98 flags:
```bash
c++ -Wall -Wextra -Werror -std=c++98
```

To compile any exercise, navigate to its directory and run `make`:
```bash
# Exercise 00
cd ex00 && make

# Exercise 01
cd ../ex01 && make

# Exercise 02
cd ../ex02 && make

# Exercise 03
cd ../ex03 && make
```

#### Makefile Targets:
- `make`: Compiles the binary.
- `make clean`: Removes intermediate object files (`.o`).
- `make fclean`: Removes object files and the generated executable.
- `make re`: Performs a complete rebuild from scratch.

### Execution
Run the compiled binaries directly to inspect the test suite outputs:

```bash
# Exercise 00
./Bureaucrat

# Exercise 01
./Bureaucrat

# Exercise 02
./forms

# Exercise 03
./forms
```

---

## Key Concepts & Architecture

1. **C++98 Exception Specifications (`throw()`)**:
   Custom exceptions inherit from `std::exception` and implement:
   ```cpp
   virtual const char* what() const throw();
   ```
   The empty exception specification `throw()` guarantees that `what()` will never throw an exception itself, satisfying the base class interface.

2. **Inverted Grade Hierarchy**:
   In the 42 bureaucratic system, **1 is the highest rank** and **150 is the lowest**. Numeric comparisons are inverted: a bureaucrat with grade 5 is *higher* than grade 20 (`5 < 20`).

3. **Strict Encapsulation**:
   All core attributes in `Form` and `AForm` are `private`, not `protected`. Derived classes interact through public getters, preserving class invariants.

4. **Member Function Pointers Table**:
   To strictly adhere to the 42 subject requirement forbidding messy `if/else if/else` structures in `Intern`, form creation is delegated through an array of member function pointers:
   ```cpp
   const FormEntry registry[] = {
       { "shrubbery creation", &Intern::_createShrubbery },
       { "robotomy request", &Intern::_createRobotomy },
       { "presidential pardon", &Intern::_createPresidential }
   };
   ```

---

## Resources
- **Bjarne Stroustrup**: *The C++ Programming Language (3rd Edition)* — Reference for C++98 exception handling and class hierarchies.
- **cppreference.com**: Documentation on `std::exception`, virtual destructors, and member function pointers.
- **42 Common Core**: *C++ Module 05 Subject (Version 11.1)*.

---

## AI Usage Disclosure
AI was utilized during this project for the following tasks:
- **Architecture Planning**: Designing the `AForm::execute` validation pipeline using the Template Method pattern to prevent code duplication across concrete forms.
- **Refactoring & Optimization**: Restructuring `Intern::makeForm` to use an array of member function pointers instead of conditional branching, satisfying the 42 evaluation criteria.
- **Error Verification & Edge Cases**: Constructing test suites in `main.cpp` to validate edge cases including boundary grades (0, 1, 150, 151), unsigned form execution, and proper memory cleanup.
