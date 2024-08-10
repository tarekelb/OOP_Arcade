##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

MAKELIB = make

all:
	$(MAKELIB) -C SFML
	$(MAKELIB) -C ALLEGRO
	$(MAKELIB) -C NCURSES

clean:
	$(MAKELIB) clean -C SFML
	$(MAKELIB) clean -C ALLEGRO
	$(MAKELIB) clean -C NCURSES

fclean: clean
	$(MAKELIB) fclean -C SFML
	$(MAKELIB) fclean -C ALLEGRO
	$(MAKELIB) fclean -C NCURSES

re: fclean all

.PHONY: all clean fclean re