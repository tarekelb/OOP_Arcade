/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGraphics
*/

#ifndef IGRAPHICS_HPP_
#define IGRAPHICS_HPP_

#include <vector>
#include <string>
#include "../InitTab.hpp"
#include "../Input.hpp"
#include "../Info.hpp"
#include <memory>

class IGraphics {
    public:
        virtual ~IGraphics() = default;
        virtual void displayGame(const std::vector<std::vector<char>> &tab) = 0;
        virtual void displayMenu(const Info &Info) = 0;
        virtual void setPreview(std::vector<std::vector<char>> &tab) = 0;
        virtual void init(const std::vector<InitTab> &tab) = 0;
        virtual void setScore(const std::string &score) = 0;
        virtual void setLife(const std::string &life) = 0;
        virtual Input getInput() = 0;
        virtual const std::string &getName(void) const = 0;

    protected:
    private:
};

#endif /* !IGRAPHICS_HPP_ */


