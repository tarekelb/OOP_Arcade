##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC = g++

SRCS = 	$(wildcard *.cpp) \

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -ldl -W -Wall -Wextra -g3

NAME = arcade

MAKELIB = make

all: core
	$(MAKELIB) -C games/
	$(MAKELIB) -C lib

graphicals:
		$(MAKELIB) -C lib

core:	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

games:
		$(MAKELIB) -C games/

clean:
	rm -rf $(OBJS)
	$(MAKELIB) clean -C lib
	$(MAKELIB) clean -C games/

fclean: clean
	rm -rf $(NAME)
	rm -rf core
	$(MAKELIB) fclean -C lib
	$(MAKELIB) fclean -C games/

re: fclean all

.PHONY: clean fclean all re games