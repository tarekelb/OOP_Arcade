/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Score
*/

#include "Score.hpp"

Score::Score(std::string name, std::string score)
{
    _name = name;
    _score = score;
}

Score::~Score()
{
}

const std::string &Score::getName() const
{
    return (this->_name);
}

const std::string &Score::getScore() const
{
    return (this->_score);
}