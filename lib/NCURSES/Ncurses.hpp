/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <ncurses.h>

#ifdef __NCURSES_H
#undef KEY_UP
#undef KEY_DOWN
#undef KEY_LEFT
#undef KEY_RIGHT
#endif

#include <sys/ioctl.h>
#include <termios.h>
#include <vector>
#include <string>
#include "InitTab.hpp"
#include "../IGraphics.hpp"
#include "Info.hpp"
#include <memory>

class Ncurses : public IGraphics {
    public:
        Ncurses();
        ~Ncurses();
        void displayGame(const std::vector<std::vector<char>> &tab) final;
        void displayMenu(const Info &Info) final;
        void setPreview(std::vector<std::vector<char>> &tab) final;
        void init(const std::vector<InitTab> &tab) final;
        void setScore(const std::string &score) final;
        void setLife(const std::string &life) final;
        Input getInput();
        const std::string &getName(void) const final;
    protected:
    private:

        std::string _name;
        std::string _score;
        std::string _life;
        std::string cutName(const std::string &str);
};

#endif /* !NCURSES_HPP_ */
