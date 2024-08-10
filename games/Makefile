##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

MAKELIB = make

all:
	$(MAKELIB) -C Nibbler
	$(MAKELIB) -C Pacman

clean:
	$(MAKELIB) clean -C Nibbler
	$(MAKELIB) clean -C Pacman

fclean: clean
	$(MAKELIB) fclean -C Nibbler
	$(MAKELIB) fclean -C Pacman

re: fclean all

.PHONY: all clean fclean re