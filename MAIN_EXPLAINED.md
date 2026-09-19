# 📖 Line-by-Line Explanation of Every `main.cpp`

This document walks through **every single line of code in the `main.cpp`** for all 4 exercises (`ex00`, `ex01`, `ex02`, `ex03`) with simple comments explaining what each line does, why it is there, and what to expect on your screen.

---

# 🔹 Exercise 00: `ex00/main.cpp`

```cpp
#include "Bureaucrat.hpp" // Includes our Bureaucrat class definition
#include <iostream>       // Needed to print messages with std::cout

int main()
{
    // ==========================================
    // TEST 1: Normal, valid Bureaucrat operations
    // ==========================================
    std::cout << "=== Valid Bureaucrat Tests ===" << std::endl;
    try
    {
        // Creates a worker named "Alnassar" with grade 75 (valid: between 1 and 150)
        Bureaucrat worker("Alnassar", 75);

        // Prints: "Alnassar, bureaucrat grade 75." using operator<<
        std::cout << worker << std::endl;

        // Promotes worker by 1 rank: grade 75 becomes 74 (subtracts 1)
        worker.incrementGrade();
        std::cout << "After promotion: " << worker << std::endl;

        // Demotes worker by 1 rank: grade 74 goes back to 75 (adds 1)
        worker.decrementGrade();
        std::cout << "After demotion:  " << worker << std::endl;
    }
    catch (const std::exception& e)
    {
        // If anything went wrong above, it would catch and print the error here
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    // ==========================================
    // TEST 2: Promoting beyond Grade 1 (Illegal!)
    // ==========================================
    std::cout << "\n=== Exception: Increment Beyond Grade 1 ===" << std::endl;
    try
    {
        // Creates a top minister with Grade 1 (the highest possible rank)
        Bureaucrat minister("Minister", 1);
        std::cout << minister << std::endl;

        std::cout << "Attempting promotion beyond grade 1..." << std::endl;
        // Grade 1 promoted -> attempts to become Grade 0 -> ILLEGAL!
        // This immediately throws Bureaucrat::GradeTooHighException!
        minister.incrementGrade();

        // Any code below the throw is SKIPPED!
        std::cout << "This will never print!" << std::endl;
    }
    catch (const std::exception& e)
    {
        // Catches GradeTooHighException and prints:
        // "Caught expected exception: Grade is too high (highest possible is 1)"
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    // ==========================================
    // TEST 3: Demoting beyond Grade 150 (Illegal!)
    // ==========================================
    std::cout << "\n=== Exception: Decrement Beyond Grade 150 ===" << std::endl;
    try
    {
        // Creates an intern with Grade 150 (the lowest possible rank)
        Bureaucrat intern("Intern", 150);
        std::cout << intern << std::endl;

        std::cout << "Attempting demotion beyond grade 150..." << std::endl;
        // Grade 150 demoted -> attempts to become Grade 151 -> ILLEGAL!
        // This immediately throws Bureaucrat::GradeTooLowException!
        intern.decrementGrade();

        // This line is skipped because of the throw above
        std::cout << "This will never print!" << std::endl;
    }
    catch (const std::exception& e)
    {
        // Catches GradeTooLowException and prints:
        // "Caught expected exception: Grade is too low (lowest possible is 150)"
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    // ==========================================
    // TEST 4: Creating workers with illegal grades
    // ==========================================
    std::cout << "\n=== Exception: Construct with Invalid Grades ===" << std::endl;
    try
    {
        // Grade 0 is illegal (< 1) -> constructor throws GradeTooHighException
        Bureaucrat god("God", 0);
    }
    catch (const std::exception& e)
    {
        std::cout << "Construct grade 0 caught:   " << e.what() << std::endl;
    }

    try
    {
        // Grade 151 is illegal (> 150) -> constructor throws GradeTooLowException
        Bureaucrat peasant("Peasant", 151);
    }
    catch (const std::exception& e)
    {
        std::cout << "Construct grade 151 caught: " << e.what() << std::endl;
    }

    return 0; // Exit successfully
}
```

---

# 🔹 Exercise 01: `ex01/main.cpp`

```cpp
#include "Bureaucrat.hpp" // Includes Bureaucrat class
#include "Form.hpp"       // Includes Form class
#include <iostream>

int main()
{
    // ==========================================
    // TEST 1: Successful Form Signing
    // ==========================================
    std::cout << "=== Testing Successful Form Signing ===" << std::endl;
    try
    {
        // Creates a boss with Grade 30
        Bureaucrat boss("Alnassar", 30);

        // Creates a form: Name="BuildingPermit", signGrade=45, execGrade=20
        // (Unsigned at start)
        Form permit("BuildingPermit", 45, 20);

        std::cout << boss << std::endl;   // Prints: Alnassar, bureaucrat grade 30.
        std::cout << permit << std::endl; // Prints: Form BuildingPermit [signed: no, grade to sign: 45...]

        // Boss (grade 30) tries to sign the permit (needs grade 45).
        // Since 30 <= 45 (rank 30 is HIGHER than 45), signing SUCCEEDS!
        // Prints: "Alnassar signed BuildingPermit"
        boss.signForm(permit);

        // Prints the form again: notice signed is now "yes"!
        std::cout << permit << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected exception: " << e.what() << std::endl;
    }

    // ==========================================
    // TEST 2: Signing with Insufficient Grade (Fails)
    // ==========================================
    std::cout << "\n=== Testing Form Signing with Insufficient Grade ===" << std::endl;
    try
    {
        // Creates a rookie worker with Grade 120 (low rank)
        Bureaucrat rookie("Rookie", 120);

        // Creates a top-secret form that requires Grade 50 to sign
        Form secretDoc("ConfidentialReport", 50, 25);

        std::cout << rookie << std::endl;
        std::cout << secretDoc << std::endl;

        // Rookie (grade 120) tries to sign secretDoc (needs grade 50).
        // Since 120 > 50 (rank 120 is LOWER than 50), Form::beSigned throws GradeTooLowException!
        // signForm catches it and prints:
        // "Rookie couldn't sign ConfidentialReport because Form grade is too low"
        rookie.signForm(secretDoc);

        // Form remains unsigned!
        std::cout << secretDoc << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected exception: " << e.what() << std::endl;
    }

    // ==========================================
    // TEST 3: Creating Forms with Invalid Grades
    // ==========================================
    std::cout << "\n=== Testing Invalid Form Construction ===" << std::endl;
    try
    {
        // Grade 0 to sign is illegal (< 1) -> throws GradeTooHighException
        Form impossible("ImpossibleForm", 0, 50);
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught expected exception (grade 0):   " << e.what() << std::endl;
    }

    try
    {
        // Grade 151 to execute is illegal (> 150) -> throws GradeTooLowException
        Form impossible2("ImpossibleForm2", 50, 151);
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught expected exception (grade 151): " << e.what() << std::endl;
    }

    return 0;
}
```

---

# 🔹 Exercise 02: `ex02/main.cpp`

```cpp
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp" // Needs sign: 145, exec: 137
#include "RobotomyRequestForm.hpp"   // Needs sign: 72,  exec: 45
#include "PresidentialPardonForm.hpp"// Needs sign: 25,  exec: 5
#include <iostream>

int main()
{
    // ==========================================
    // STEP 1: Create 3 bureaucrats with different ranks
    // ==========================================
    std::cout << "=== Creating Bureaucrats ===" << std::endl;
    Bureaucrat president("Alnassar", 1);  // Grade 1: Can do everything
    Bureaucrat manager("Manager", 40);    // Grade 40: Mid-level
    Bureaucrat trainee("Trainee", 140);   // Grade 140: Low-level

    std::cout << president << std::endl;
    std::cout << manager << std::endl;
    std::cout << trainee << std::endl;

    // ==========================================
    // TEST 1: ShrubberyCreationForm (sign 145, exec 137)
    // ==========================================
    std::cout << "\n=== Testing ShrubberyCreationForm ===" << std::endl;
    // Creates shrubbery form targeted at "garden"
    ShrubberyCreationForm shrub("garden");
    std::cout << shrub << std::endl;

    // Manager tries to execute BEFORE it's signed:
    // FAILS! Prints: "Manager couldn't execute ShrubberyCreationForm because Form is not signed"
    manager.executeForm(shrub);

    // Trainee (grade 140 <= 145) signs the form: SUCCEEDS!
    trainee.signForm(shrub);

    // Manager (grade 40 <= 137) executes it: SUCCEEDS!
    // Creates the file "garden_shrubbery" and writes ASCII trees inside it!
    manager.executeForm(shrub);

    // ==========================================
    // TEST 2: RobotomyRequestForm (sign 72, exec 45)
    // ==========================================
    std::cout << "\n=== Testing RobotomyRequestForm ===" << std::endl;
    // Creates robotomy form targeted at "Bender"
    RobotomyRequestForm robotomy("Bender");
    std::cout << robotomy << std::endl;

    // Manager (grade 40 <= 72) signs it: SUCCEEDS!
    manager.signForm(robotomy);

    // Manager (grade 40 <= 45) executes it: SUCCEEDS!
    // Makes drilling noises "* BZZZZZZT! *" and has a 50% chance of success!
    manager.executeForm(robotomy);

    // ==========================================
    // TEST 3: PresidentialPardonForm (sign 25, exec 5)
    // ==========================================
    std::cout << "\n=== Testing PresidentialPardonForm ===" << std::endl;
    // Creates pardon form targeted at "Ford Prefect"
    PresidentialPardonForm pardon("Ford Prefect");
    std::cout << pardon << std::endl;

    // Manager (grade 40) tries to sign (needs 25):
    // FAILS! Prints: "Manager couldn't sign... because Form grade is too low"
    manager.signForm(pardon);

    // President (grade 1 <= 25) signs it: SUCCEEDS!
    president.signForm(pardon);

    // Manager (grade 40) tries to execute (needs 5):
    // FAILS! Prints: "Manager couldn't execute... because Form grade is too low"
    manager.executeForm(pardon);

    // President (grade 1 <= 5) executes it: SUCCEEDS!
    // Prints: "Ford Prefect has been pardoned by Zaphod Beeblebrox."
    president.executeForm(pardon);

    return 0;
}
```

---

# 🔹 Exercise 03: `ex03/main.cpp`

```cpp
#include "Bureaucrat.hpp"
#include "Intern.hpp"     // Includes Intern class
#include "AForm.hpp"      // Includes base AForm pointer
#include <iostream>

int main()
{
    // The Intern has no name and no grade
    Intern someRandomIntern;
    Bureaucrat boss("Alnassar", 1); // Grade 1 boss to test signing & executing

    // ==========================================
    // TEST 1: Intern creates a RobotomyRequestForm
    // ==========================================
    std::cout << "=== Intern Creates Valid Forms ===" << std::endl;
    // Intern looks up "robotomy request" in its function pointer table.
    // Finds it -> prints "Intern creates robotomy request"
    // Returns a new RobotomyRequestForm("Bender") allocated on the heap!
    AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
    if (rrf)
    {
        boss.signForm(*rrf);    // Boss signs the form
        boss.executeForm(*rrf); // Boss executes the form
        delete rrf;             // IMPORTANT: Frees heap memory (no memory leaks!)
    }

    // ==========================================
    // TEST 2: Intern creates a ShrubberyCreationForm
    // ==========================================
    std::cout << "\n=== Intern Creates Shrubbery Form ===" << std::endl;
    // Intern looks up "shrubbery creation" -> creates ShrubberyCreationForm("courtyard")
    AForm* scf = someRandomIntern.makeForm("shrubbery creation", "courtyard");
    if (scf)
    {
        boss.signForm(*scf);
        boss.executeForm(*scf);
        delete scf;             // Clean up memory
    }

    // ==========================================
    // TEST 3: Intern creates a PresidentialPardonForm
    // ==========================================
    std::cout << "\n=== Intern Creates Presidential Pardon Form ===" << std::endl;
    // Intern looks up "presidential pardon" -> creates PresidentialPardonForm("Arthur Dent")
    AForm* ppf = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
    if (ppf)
    {
        boss.signForm(*ppf);
        boss.executeForm(*ppf);
        delete ppf;             // Clean up memory
    }

    // ==========================================
    // TEST 4: Intern tries to create an UNKNOWN form
    // ==========================================
    std::cout << "\n=== Intern Tries Unknown Form ===" << std::endl;
    // "coffee request" does NOT exist in the table!
    // Intern prints: "Intern cannot create coffee request because the form type is unknown."
    // Returns NULL!
    AForm* unknown = someRandomIntern.makeForm("coffee request", "Boss");
    if (unknown)
    {
        delete unknown;
    }
    // If unknown is NULL, it cleanly skips without crashing!

    return 0; // Everything passed!
}
```
