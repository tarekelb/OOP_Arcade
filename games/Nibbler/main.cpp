/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

/*
** Compile dans le repo du nibbler
** g++ nibbler.cpp main.cpp ../../InitTab.cpp -g3 -o nibbler
** Executer nibbler et entrer z, q, s, d pour move
** 'stop' pour sortir
*/

#include "nibbler.hpp"
#include <ctime>
// #include "../../lib/SFML/SFML.hpp"
#include "../../lib/ALLEGRO/Allegro.hpp"
#include <unistd.h>

void printVector(std::vector<std::vector<char>> vector)
{
    for (size_t idx_x = 0; idx_x < vector.size(); idx_x++) {
        for (size_t idx_y = 0; idx_y < vector[idx_x].size(); idx_y++) {
            std::cout << vector[idx_x][idx_y];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(void)
{
    nibbler nibbler;
    std::string str;
    Allegro sfml;
    std::vector<std::vector<char>> vector;

    sfml.init(nibbler.getInit());
    while (1) {
        usleep(95000);
        vector = nibbler.simulate(sfml.getInput());
        sfml.setLife(nibbler.getLife());
        sfml.setScore(nibbler.getScore());
        sfml.displayGame(vector);
        //printVector(vector);
        if (nibbler.getLife() == "0") {
            exit (84);
        }
    }
}