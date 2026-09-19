# 📚 CPP Module 05: Complete Study Guide & Code Walkthrough

This study guide explains **CPP Module 05** in plain, simple English. It goes through every concept and every exercise line-by-line so you can fully understand the code and confidently answer any question during your 42 peer evaluation.

---

## 📑 Table of Contents
1. [Core Concepts: What You Need to Know First](#1-core-concepts-what-you-need-to-know-first)
2. [The Inverted Grade System (The Tricky Part)](#2-the-inverted-grade-system-the-tricky-part)
3. [Exercise 00: Bureaucrat](#3-exercise-00-bureaucrat)
4. [Exercise 01: Form](#4-exercise-01-form)
5. [Exercise 02: AForm & The 3 Concrete Forms](#5-exercise-02-aform--the-3-concrete-forms)
6. [Exercise 03: Intern](#6-exercise-03-intern)
7. [Top Evaluation Questions & Answers](#7-top-evaluation-questions--answers)

---

## 1. Core Concepts: What You Need to Know First

### A. The Real-World Metaphor: The Government Office
Think of a bureaucratic government office (like a ministry or the DMV):
- **`Bureaucrat`**: An office employee. Each employee has a **rank/grade** from 1 to 150.
- **`Form` / `AForm`**: Paperwork that needs stamps. Each document requires a minimum rank to **sign**, and a minimum rank to **execute**.
- **`Intern`**: An unpaid worker who creates blank forms on demand.

### B. What is an Exception? (`try`, `catch`, `throw`)
In the C language, when a function failed, you returned an error code like `-1` or `NULL`:
```c
int fd = open("file.txt", O_RDONLY);
if (fd == -1) { /* error */ }
```
**The problem with C:** If the programmer forgot to write the `if` check, the program kept running with corrupt data and crashed later.

In C++, we use **Exceptions**:
```cpp
try {
    Bureaucrat worker("John", 0); // Invalid grade!
}
catch (const std::exception& e) {
    std::cout << e.what() << std::endl; // Catches the error!
}
```
1. **`throw`**: When something goes wrong, you throw an exception object. Normal execution stops immediately.
2. **`try`**: Wraps the code that might cause an error.
3. **`catch`**: Catches the thrown error and handles it. An exception **cannot be accidentally ignored**.

### C. What is Orthodox Canonical Form (OCF)?
42 requires every class to have these 4 member functions:
1. **Default constructor**: Initializes default values (e.g. `Bureaucrat()`).
2. **Copy constructor**: Creates a clone of an existing object (e.g. `Bureaucrat(const Bureaucrat& other)`).
3. **Copy assignment operator**: Copies data from one existing object into another (e.g. `operator=`).
4. **Destructor**: Cleans up resources when the object dies (e.g. `~Bureaucrat()`).

---

## 2. The Inverted Grade System (The Tricky Part)

> **Grade 1 = Highest Rank (The President)**  
> **Grade 150 = Lowest Rank (The Beginner)**

Remember:
- **Higher rank = smaller number** (Grade 1 is better than Grade 2).
- **Lower rank = larger number** (Grade 150 is worse than Grade 149).

### How this affects Increment & Decrement:
- **`incrementGrade()` (Promotion)**:
  - If you get promoted, your rank improves, so the number gets **SMALLER**!
  - Grade 3 becomes Grade 2 (`--_grade`).
  - If you are at Grade 1 and try to increment, you would become Grade 0. **0 is too high! Throw `GradeTooHighException`!**
- **`decrementGrade()` (Demotion)**:
  - If you get demoted, your rank drops, so the number gets **BIGGER**!
  - Grade 3 becomes Grade 4 (`++_grade`).
  - If you are at Grade 150 and try to decrement, you would become Grade 151. **151 is too low! Throw `GradeTooLowException`!**

---

## 3. Exercise 00: Bureaucrat

### Purpose
Create a `Bureaucrat` class with boundary protection on its grade.

### Header Breakdown (`Bureaucrat.hpp`)
```cpp
class Bureaucrat
{
private:
    const std::string _name;  // Constant name (cannot be changed after creation)
    int               _grade; // Grade between 1 and 150

public:
    Bureaucrat();
    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& rhs);
    ~Bureaucrat();

    const std::string& getName() const;
    int                getGrade() const;

    void incrementGrade();
    void decrementGrade();

    // Custom Exception Classes
    class GradeTooHighException : public std::exception {
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
        virtual const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);
```

### Key Functions Explained:

#### 1. Why does `what()` have `throw()` at the end?
```cpp
virtual const char* what() const throw();
```
- `what()` returns an error description string (`const char*`).
- `throw()` is an **exception specification**. It promises the compiler: *"Calling `what()` will NEVER throw an exception itself."*
- If you don't write `throw()`, the compiler will give an error because the parent class `std::exception` declares it with `throw()`.

#### 2. Constructor Range Check (`Bureaucrat.cpp`)
```cpp
Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : _name(name), _grade(grade)
{
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}
```
If an invalid grade is passed, the constructor immediately throws an exception before the object is finished building.

#### 3. Output Operator (`<<`)
```cpp
std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat)
{
    os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
    return os;
}
```
Allows printing directly: `std::cout << worker << std::endl;`.  
*Note:* The subject explicitly requires the output to end with a period `.`.

---

## 4. Exercise 01: Form

### Purpose
Create a `Form` class that a `Bureaucrat` can sign.

### Form Attributes (Must be `private`!)
```cpp
private:
    const std::string _name;           // Form name (constant)
    bool              _isSigned;       // Starts as false
    const int         _gradeToSign;    // Minimum grade needed to sign (constant)
    const int         _gradeToExecute; // Minimum grade needed to execute (constant)
```
> **Why are they `private` and `const`?**  
> To protect the data (encapsulation). Once a form exists, you should never be able to tamper with its required grades or name. Only `_isSigned` changes when it gets signed.

### How Signing Works (`beSigned` & `signForm`)

#### In `Form.cpp`:
```cpp
void Form::beSigned(const Bureaucrat& bureaucrat)
{
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}
```
- Remember: **Bigger number = lower rank**.
- If a form requires grade 50:
  - A bureaucrat of grade 30 tries to sign: `30 > 50` is `false`. Grade is high enough! Form is signed.
  - A bureaucrat of grade 80 tries to sign: `80 > 50` is `true`. Grade is too low! Throws `GradeTooLowException`.

#### In `Bureaucrat.cpp`:
```cpp
void Bureaucrat::signForm(Form& form)
{
    try {
        form.beSigned(*this);
        std::cout << _name << " signed " << form.getName() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << _name << " couldn't sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
```
The bureaucrat attempts to sign. If an exception is thrown, it catches it and prints a polite error message instead of crashing.

---

## 5. Exercise 02: AForm & The 3 Concrete Forms

### What changes from Ex01?
1. `Form` becomes **`AForm`** (Abstract Form).
2. It has a **pure virtual function**:
   ```cpp
   virtual void executeAction() const = 0;
   ```
   Because of `= 0`, `AForm` is an **abstract class**. You cannot create an `AForm` directly (`AForm f;` is illegal). You can only create child forms that implement `executeAction()`.

### The Template Method Pattern (The Elegant Approach)
In `AForm.cpp`:
```cpp
void AForm::execute(const Bureaucrat& executor) const
{
    // Step 1: Is the form signed?
    if (!_isSigned)
        throw FormNotSignedException();

    // Step 2: Is the bureaucrat's grade high enough to execute?
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();

    // Step 3: All checks passed -> execute the specific form's action!
    executeAction();
}
```
**Why is this elegant?**  
The validation logic (is it signed? is rank high enough?) is written **once** in the base class `AForm`. The child classes only focus on their unique action.

### The 3 Concrete Forms:

| Form | Sign Grade | Exec Grade | What `executeAction()` does |
| :--- | :---: | :---: | :--- |
| **`ShrubberyCreationForm`** | 145 | 137 | Opens a file named `<target>_shrubbery` and writes ASCII trees into it. |
| **`RobotomyRequestForm`** | 72 | 45 | Makes drilling sounds (`* BZZZZZZT! *`), then 50% of the time succeeds and 50% fails using `std::rand()`. |
| **`PresidentialPardonForm`** | 25 | 5 | Informs that `<target>` has been pardoned by Zaphod Beeblebrox. |

---

## 6. Exercise 03: Intern

### What is the Intern?
The `Intern` has no name and no grade. His only job is to create forms using:
```cpp
AForm* makeForm(const std::string& formName, const std::string& target) const;
```

### The 42 Requirement: NO `if / else if` Chains!
The subject strictly warns:
> *"You must avoid unreadable and messy solutions, such as using an excessive if/elseif/else structure."*

### How We Solve It: Array of Pointers to Member Functions

#### Step 1: Define the function pointer type
```cpp
typedef AForm* (Intern::*FormCreator)(const std::string& target) const;
```
This defines a type named `FormCreator` that points to a member function of `Intern` taking a `target` string and returning `AForm*`.

#### Step 2: Define private creator functions in `Intern.hpp`
```cpp
AForm* _createShrubbery(const std::string& target) const;
AForm* _createRobotomy(const std::string& target) const;
AForm* _createPresidential(const std::string& target) const;
```

#### Step 3: Create the lookup table (Registry) in `Intern.cpp`
```cpp
AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
    const FormEntry registry[] = {
        { "shrubbery creation",  &Intern::_createShrubbery },
        { "robotomy request",    &Intern::_createRobotomy },
        { "presidential pardon", &Intern::_createPresidential }
    };

    for (int i = 0; i < 3; ++i)
    {
        if (formName == registry[i].name)
        {
            std::cout << "Intern creates " << formName << std::endl;
            // Call the member function through its pointer:
            return (this->*(registry[i].create))(target);
        }
    }

    // If no form matches:
    std::cout << "Intern cannot create " << formName
              << " because the form type is unknown." << std::endl;
    return NULL;
}
```
**Why this is great:** If you need to add 10 new forms in the future, you just add entries to the array — you never have to write another `else if`!

---

## 7. Top Evaluation Questions & Answers

### Q1: "Why does `incrementGrade()` decrease the grade number?"
> **Answer**: "Because in the 42 bureaucracy, Grade 1 is the highest rank and Grade 150 is the lowest. A promotion (increment) means you move closer to rank 1, so the number decreases (e.g. from 3 to 2)."

### Q2: "Why do custom exceptions inherit from `std::exception`?"
> **Answer**: "So that all exceptions in our program can be caught with a single generic `catch (const std::exception& e)` block, which is standard C++ polymorphism."

### Q3: "Why is the destructor in `AForm` virtual?"
> **Answer**: "Because `AForm` is a base class. If we delete a derived form through a base pointer (`AForm* form = new ShrubberyCreationForm(); delete form;`), a virtual destructor guarantees that the derived destructor runs first. If it weren't virtual, only the base destructor would run, causing memory leaks."

### Q4: "Why are `Form` attributes private instead of protected?"
> **Answer**: "Encapsulation. Derived classes should not have direct write access to sensitive state like `_isSigned` or the grades. Instead, they access them via public getters, preserving class invariants."

### Q5: "How does `Intern::makeForm` work without `if/else`?"
> **Answer**: "It uses an array of structs pairing form names with pointers to member functions. It loops through the array, finds the matching name, and invokes the function pointer `(this->*(registry[i].create))(target)`. If none match, it returns `NULL`."
