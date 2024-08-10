##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CXX = g++

SRCS =		Allegro.cpp \
			InitTab.cpp	\
			Score.cpp	\
			Info.cpp

ALFLAGS	=	`pkg-config --libs allegro-5 allegro_font-5 allegro_image-5 allegro_ttf-5 allegro_dialog-5 allegro_main-5 allegro_primitives-5`

CXXFLAGS =	-W -Wall -Wextra -fPIC -g3

NAME = ../lib_arcade_allegro.so

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
			$(CXX) -shared $(OBJS) -o $(NAME) $(LDFLAGS) $(ALFLAGS)

clean:
	rm -f *.o

fclean:	clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re