##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CXX = g++

SRCS =		Ncurses.cpp \
			InitTab.cpp	\
			Info.cpp \
			Score.cpp

NCFLAGS =	-lncurses

CXXFLAGS =	-w -Wall -Wextra -fPIC -g3

NAME = ../lib_arcade_ncurses.so

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
			$(CXX) -shared $(OBJS) -o $(NAME) $(LDFLAGS) $(NCFLAGS)

clean:
	rm -f *.o

fclean:	clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re