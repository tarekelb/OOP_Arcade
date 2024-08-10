/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Ghost
*/

#include "Ghost.hpp"

Ghost::Ghost(const size_t &x, const size_t &y, const size_t &respawn, const char &character, const char &character1)
{
    this->_pos = {x, y};
    this->_respawnPos = {x, y};
    this->_respawn = respawn;
    this->_character = character;
    this->_character1 = character1;
    this->_active = true;
    this->_way = NONE;
}

void Ghost::moveGhost(std::vector<std::vector<char>> &stock)
{
    std::vector<Input> move;
    int idx = 0;

    if (this->_respawn != 0) {
        this->_respawn--;
        return;
    }
    if (this->_pos.first == 0 || stock[this->_pos.first - 1][this->_pos.second] != '#') {
        move.push_back(KEY_UP);
    }
    if (this->_pos.first == stock.size() - 1 || stock[this->_pos.first + 1][this->_pos.second] != '#') {
        move.push_back(KEY_DOWN);
    }
    if (this->_pos.second == 0 || stock[this->_pos.first][this->_pos.second - 1] != '#') {
        move.push_back(KEY_LEFT);
    }
    if (this->_pos.second == stock[this->_pos.first].size() - 1 || stock[this->_pos.first][this->_pos.second + 1] != '#') {
        move.push_back(KEY_RIGHT);
    }
    if (this->_way == NONE) {
        this->_way = move[std::rand() % move.size()];
    } else if (this->_way == KEY_UP) {
        this->_way = KEY_DOWN;
        for (; idx < 10 && this->_way == KEY_DOWN; idx++) {
            this->_way = move[rand() % move.size()];
        }
    } else if (this->_way == KEY_DOWN) {
        this->_way = KEY_UP;
        for (; idx < 10 && this->_way == KEY_UP; idx++) {
            this->_way = move[rand() % move.size()];
        }
    } else if (this->_way == KEY_LEFT) {
        this->_way = KEY_RIGHT;
        for (; idx < 10 && this->_way == KEY_RIGHT; idx++) {
            this->_way = move[rand() % move.size()];
        }
    } else if (this->_way == KEY_RIGHT) {
        this->_way = KEY_LEFT;
        for (; idx < 10 && this->_way == KEY_LEFT; idx++) {
            this->_way = move[rand() % move.size()];
        }
    }

    if (this->_way == KEY_UP) {
        if (this->_pos.first == 0) {
            this->_pos.first = stock.size() - 1;
        } else {
            this->_pos.first--;
        }
    } else if (this->_way == KEY_DOWN) {
        if (this->_pos.first == stock.size() - 1) {
            this->_pos.first = 0;
        } else {
            this->_pos.first++;
        }
    } else if (this->_way == KEY_LEFT) {
        if (this->_pos.second == 0) {
            this->_pos.second = stock[this->_pos.first].size() - 1;
        } else {
            this->_pos.second--;
        }
    } else if (this->_way == KEY_RIGHT) {
        if (this->_pos.second == stock[this->_pos.first].size() - 1) {
            this->_pos.second = 0;
        } else {
            this->_pos.second++;
        }
    }
    if (this->_active) {
        if (this->_way == KEY_LEFT) {
            stock[this->_pos.first][this->_pos.second] = this->_character;
        } else if (this->_way == KEY_RIGHT) {
            stock[this->_pos.first][this->_pos.second] = this->_character1;
        } else {
            if (this->_pos.second < stock[this->_pos.first].size() / 2) {
                stock[this->_pos.first][this->_pos.second] = this->_character;
            } else {
                stock[this->_pos.first][this->_pos.second] = this->_character1;
            }
        }
    } else {
        stock[this->_pos.first][this->_pos.second] = '~';
    }
}

void Ghost::killGhost()
{
    this->_active = true;
    this->setPos(this->_respawnPos.first, this->_respawnPos.second);
    this->setRespawn(30);
}

const size_t &Ghost::getRespawn() const
{
    return this->_respawn;
}

const std::pair<size_t, size_t> &Ghost::getPos() const
{
    return this->_pos;
}

const bool &Ghost::getActive() const
{
    return this->_active;
}

void Ghost::setPos(const size_t &x, const size_t &y)
{
    this->_pos.first = x;
    this->_pos.second = y;
}

void Ghost::setActive(const bool &state)
{
    this->_active = state;
}

void Ghost::setRespawn(const size_t &respawn)
{
    this->_respawn = respawn;
}

Ghost::~Ghost()
{
}
