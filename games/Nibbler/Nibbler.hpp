/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** nibbler
*/

#ifndef Nibbler_HPP_
#define Nibbler_HPP_

#include "../IGame.hpp"

class Nibbler : public IGames {
    public:
        Nibbler();
        ~Nibbler();
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
        std::vector<std::pair<size_t, size_t>> _snake;
        std::pair<size_t, size_t> _apple;
        Input _way;
        size_t _respawn;
        size_t _respawn_max;
        float _speed;

        void generateMap(std::string name);
        void copyMap();
        void fillMap();
        void generateInit();
        void movenibbler();
        void generateApple();
        void getDamage();
        void createSnake();
};

#endif /* !Nibbler_HPP_ */
