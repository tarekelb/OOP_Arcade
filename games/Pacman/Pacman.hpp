/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "../IGame.hpp"
#include "Ghost.hpp"

class Pacman : public IGames {
    public:
        Pacman();
        ~Pacman();
        const std::vector<std::vector<char>> &simulate(Input key) final;
        const std::string &getScore() const final;
        const std::string &getLife() const final;
        const std::vector<InitTab> &getInit() const final;
        const float &getSpeed(void) const final;

    protected:
    private:
        std::vector<std::vector<char>> _map;
        std::vector<std::vector<char>> _stock;
        std::string _score;
        std::string _life;
        std::vector<InitTab> _init;
        std::pair<size_t, size_t> _player;
        std::vector<Ghost> _ghosts;
        Input _way;
        size_t _super;
        std::pair<size_t, size_t> _respawnPac;
        std::pair<size_t, size_t> _respawnGhost;
        float _speed;

        void generateMap(std::string name);
        void generateInit();
        void generateMonster();
        void superGum();
        void checkInput(Input key);
        void movePacman();
        void copyMap();
        void fillMap();
        void checkEnd();
        void reset();
};

#endif /* !PACMAN_HPP_ */
