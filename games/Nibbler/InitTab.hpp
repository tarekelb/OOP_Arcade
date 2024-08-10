/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** InitTab
*/

#ifndef INITTAB_HPP_
#define INITTAB_HPP_

#include <string>
#include <vector>

class InitTab {
    public:
        InitTab(char c, int iC, int oC, const std::string &str);
        ~InitTab();
        char getCharacter() const;
        int getInColor() const;
        int getOutColor() const;
        const std::string &getPath() const;

    private:
        char _c;
        int _inColor;
        int _outColor;
        std::string _path;
};

#endif /* !INITTAB_HPP_ */
