/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Info
*/

#ifndef Info_HPP_
#define Info_HPP_

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <dirent.h>
#include "Score.hpp"


class Info {
    public:
        Info(const std::string &lib);
        ~Info();
        const std::vector<std::string> &getGraphNames() const;
        const std::vector<std::string> &getGameNames() const;
        const std::string &getGameSelected() const;
        const std::string &getGraphSelected() const;
        void setListNames(const std::string &name,  std::vector<std::string> &list);
        size_t getGraphIdx() const;
        size_t getGameIdx() const;
        size_t getSide() const;
        const std::vector<Score> &getScoring() const;
        void setGameIdx(const size_t &idx);
        void setGraphIdx(const size_t &idx);
        void setSide(const size_t &side);
        void setScoring(const std::string &file);
        void addScore(const Score &score);

    protected:
    private:
        std::vector<std::string> _graphNames;
        std::vector<std::string> _gameNames;
        size_t _gameIdx;
        size_t _graphIdx;
        size_t _side;
        std::vector<Score> _scoring;

};

#endif /* !Info_HPP_ */
