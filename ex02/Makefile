# Compiler and flags
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Executable name
NAME = forms

# Source files
SRCS = main.cpp \
       Bureaucrat.cpp \
       AForm.cpp \
       ShrubberyCreationForm.cpp \
       RobotomyRequestForm.cpp \
       PresidentialPardonForm.cpp

# Object files (same names but .o)
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = Bureaucrat.hpp AForm.hpp \
          ShrubberyCreationForm.hpp \
          RobotomyRequestForm.hpp \
          PresidentialPardonForm.hpp

# Default target
all: $(NAME)

# Link executable
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

# Compile .cpp → .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re
