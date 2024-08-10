/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include "Info.hpp"
#include "games/IGame.hpp"
#include "lib/IGraphics.hpp"
#include "Input.hpp"

class Core {
    public:
        Core(const std::string &lib);
        ~Core();
        void MainLoop();

    protected:
    private:
        Info _Info;
        std::unique_ptr<IGraphics> _Graphic;
        std::unique_ptr<IGames> _Game;
        void *handleGraphic;
        void *handleGame;
        std::string getGameNameSelected() const;
        void LoadGraph();
        void LoadGame();
        void swapNextGraph();
        void swapPrevGraph();
        void swapNextGame();
        void swapPrevGame();
        void GameLoop();
};
#endif /* !CORE_HPP_ */
