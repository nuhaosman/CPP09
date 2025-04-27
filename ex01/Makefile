NAME = RPN
CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror
STD = -std=c++98

SRC =	main.cpp \
		RPN.cpp

$(NAME): $(SRC)
	$(CPP) $(CPP_FLAGS) $(STD) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	rm -fr $(NAME)

fclean: clean

re: fclean all