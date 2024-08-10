/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
#define GHOST_HPP_

#include <vector>
#include <iostream>
#include "../../Input.hpp"

class Ghost {
    public:
        Ghost(const size_t &x, const size_t &y, const size_t &respawn, const char &character, const char &character1);
        ~Ghost();
        void setPos(const size_t &x, const size_t &y);
        void setActive(const bool &);
        void setRespawn(const size_t &respawn);
        const size_t &getRespawn() const;
        const std::pair<size_t, size_t> &getPos() const;
        const bool &getActive() const;
        void moveGhost(std::vector<std::vector<char>> &stock);
        void killGhost();


    protected:
    private:
        std::pair<size_t, size_t> _pos;
        std::pair<size_t, size_t> _respawnPos;
        char _character;
        char _character1;
        bool _active;
        Input _way;
        size_t _respawn;

};
#endif /* !GHOST_HPP_ */
