##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CXX = g++

SRCS =		Nibbler.cpp \
			InitTab.cpp

CXXFLAGS =	-W -Wall -Wextra -fPIC

NAME = ../lib_arcade_nibbler.so

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
			$(CXX) -shared $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f *.o

fclean:	clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
