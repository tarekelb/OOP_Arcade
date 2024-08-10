/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGames
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../InitTab.hpp"
#include "../Input.hpp"
#include "../Info.hpp"
#include <memory>

class IGames {
    public:
        virtual ~IGames() = default;
        virtual const std::vector<std::vector<char>> &simulate(Input key) = 0;
        virtual const std::string &getScore() const = 0;
        virtual const std::string &getLife() const = 0;
        virtual const std::vector<InitTab> &getInit() const = 0;
        virtual const float &getSpeed(void) const = 0;
    protected:
    private:
};

#endif /* !IGAMES_HPP_ */
