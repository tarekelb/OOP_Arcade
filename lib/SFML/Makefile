##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CXX = g++

SRCS =		SFML.cpp \
			InitTab.cpp	\
			Info.cpp \
			Score.cpp

SFFLAGS =	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CXXFLAGS =	-w -Wall -Wextra -fPIC -g3

NAME = ../lib_arcade_sfml.so

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
			$(CXX) -shared $(OBJS) -o $(NAME) $(LDFLAGS) $(SFFLAGS)

clean:
	rm -f *.o

fclean:	clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re