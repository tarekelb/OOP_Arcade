/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(const std::string &lib) : _Info(lib)
{
    this->handleGraphic = NULL;
    this->handleGame = NULL;
}

Core::~Core()
{
    this->_Graphic.reset();
    this->_Game.reset();
    dlclose(this->handleGame);
    dlclose(this->handleGraphic);
}

std::string Core::getGameNameSelected() const
{
    std::string tmp = this->_Info.getGameSelected().substr(this->_Info.getGameSelected().find_last_of('_') + 1);
    tmp[0] = std::toupper(tmp[0]);
    tmp = tmp.substr(0, tmp.find('.'));
    return tmp;
}

void Core::swapNextGraph()
{
    std::vector<std::string> tmp = this->_Info.getGraphNames();

    if (tmp.size() == 1) {
        return;
    } else if (this->_Info.getGraphIdx() == tmp.size() - 1) {
        this->_Info.setGraphIdx(0);
    } else {
        this->_Info.setGraphIdx(this->_Info.getGraphIdx() + 1);
    }
    this->LoadGraph();
}

void Core::swapPrevGraph()
{
    std::vector<std::string> tmp = this->_Info.getGraphNames();

    if (tmp.size() == 1) {
        return;
    } else if (this->_Info.getGraphIdx() == 0) {
        this->_Info.setGraphIdx(tmp.size() - 1);
    } else {
        this->_Info.setGraphIdx(this->_Info.getGraphIdx() - 1);
    }
    this->LoadGraph();
}

void Core::swapNextGame()
{
    std::vector<std::string> tmp = this->_Info.getGameNames();

    if (tmp.size() == 1) {
        return;
    } else if (this->_Info.getGameIdx() == tmp.size() - 1) {
        this->_Info.setGameIdx(0);
    } else {
        this->_Info.setGameIdx(this->_Info.getGameIdx() + 1);
    }
    this->LoadGame();
}

void Core::swapPrevGame()
{
    std::vector<std::string> tmp = this->_Info.getGameNames();

    if (tmp.size() == 1) {
        return;
    } else if (this->_Info.getGameIdx() == 0) {
        this->_Info.setGameIdx(tmp.size() - 1);
    } else {
        this->_Info.setGameIdx(this->_Info.getGameIdx() - 1);
    }
    this->LoadGame();
}

void Core::LoadGraph()
{
    if (this->handleGraphic) {
        this->_Graphic.reset();
        dlclose(this->handleGraphic);
    }
    this->handleGraphic = dlopen(_Info.getGraphSelected().c_str(), RTLD_LAZY);
    if (!handleGraphic) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    std::unique_ptr<IGraphics> (*createGraphics)();

    createGraphics = (std::unique_ptr<IGraphics> (*)())dlsym(handleGraphic, "createInterface");

    this->_Graphic = createGraphics();
    if (this->_Game) {
        this->_Graphic->init(this->_Game->getInit());
    }
}

void Core::LoadGame()
{
    if (this->handleGame) {
        IGames *tmp = this->_Game.release();
        dlclose(this->handleGame);
    }
    this->handleGame = dlopen(_Info.getGameSelected().c_str(), RTLD_LAZY);
    if (!handleGame) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    std::unique_ptr<IGames> (*createGames)();

    createGames = (std::unique_ptr<IGames> (*)())dlsym(handleGame, "createInterface");

    this->_Game = createGames();
}

void Core::GameLoop()
{
    std::string _name;
    Input tmp = NONE;

    LoadGame();
    LoadGraph();
    _name = _Graphic->getName().size() ? _Graphic->getName() : "UNKNOWN";
    tmp = NONE;
    while (1) {
        usleep(100000 / this->_Game->getSpeed());
        tmp = _Graphic->getInput();
        if (tmp == NEXT_GRAPH) {
            this->swapNextGraph();
            tmp = NONE;
        } else if (tmp == PREV_GRAPH) {
            this->swapPrevGraph();
            tmp = NONE;
        } else if (tmp == NEXT_GAME) {
            this->swapNextGame();
            this->_Graphic->init(this->_Game->getInit());
            tmp = NONE;
            continue;
        } else if (tmp == PREV_GAME) {
            this->swapPrevGame();
            this->_Graphic->init(this->_Game->getInit());
            tmp = NONE;
            continue;
        } else if (tmp == EXIT) {
            return this->MainLoop();
        } else if (tmp == ENTER) {
            this->LoadGame();
            this->_Graphic->init(this->_Game->getInit());
        }
        _Graphic->setLife(_Game->getLife());
        _Graphic->setScore(_Game->getScore());
        _Graphic->displayGame(_Game->simulate(_Graphic->getInput()));
        if (_Game->getLife() == "0") {
            this->_Info.addScore(Score(_name, _Game->getScore()));
            exit (84);
        }
    }
}

void Core::MainLoop()
{
    Input tmp = NONE;
    this->_Info.setScoring(this->_Info.getGameSelected().substr(0, this->_Info.getGameSelected().find_last_of('/') + 1) + getGameNameSelected() + "/Score.txt");

    LoadGraph();
    while (1) {
        usleep(95000);
        tmp = _Graphic->getInput();
        if (tmp == KEY_LEFT && this->_Info.getSide() != 2) {
            if (this->_Info.getSide() == 2) {
                this->_Info.setSide(1);
            } else if (this->_Info.getSide() == 1) {
                this->_Info.setSide(0);
            } else if (this->_Info.getSide() == 0) {
                this->_Info.setSide(2);
            }
        } else if (tmp == KEY_RIGHT && this->_Info.getSide() != 2) {
            if (this->_Info.getSide() == 2) {
                this->_Info.setSide(0);
            } else if (this->_Info.getSide() == 1) {
                this->_Info.setSide(2);
            } else if (this->_Info.getSide() == 0) {
                this->_Info.setSide(1);
            }
        } else if (tmp == KEY_UP && this->_Info.getSide() != 2) {
            if (this->_Info.getSide() == 1) {
                if (this->_Info.getGraphIdx() == 0) {
                    this->_Info.setGraphIdx(this->_Info.getGraphNames().size() - 1);
                } else if (this->_Info.getGraphNames().size() > 1) {
                    this->_Info.setGraphIdx(this->_Info.getGraphIdx() - 1);
                }
            } else if (this->_Info.getSide() == 0) {
                if (this->_Info.getGameIdx() == 0) {
                    this->_Info.setGameIdx(this->_Info.getGameNames().size() - 1);
                        this->_Info.setScoring(this->_Info.getGameSelected().substr(0, this->_Info.getGameSelected().find_last_of('/') + 1) + getGameNameSelected() + "/Score.txt");
                } else if (this->_Info.getGameNames().size() > 1) {
                    this->_Info.setGameIdx(this->_Info.getGameIdx() - 1);
                    this->_Info.setScoring(this->_Info.getGameSelected().substr(0, this->_Info.getGameSelected().find_last_of('/') + 1) + getGameNameSelected() + "/Score.txt");
                }
            }
        } else if (tmp == KEY_DOWN && this->_Info.getSide() != 2) {
            if (this->_Info.getSide() == 1) {
                if (this->_Info.getGraphIdx() == this->_Info.getGraphNames().size() - 1) {
                    this->_Info.setGraphIdx(0);
                } else if (this->_Info.getGraphNames().size() > 1) {
                    this->_Info.setGraphIdx(this->_Info.getGraphIdx() + 1);
                }
            } else if (this->_Info.getSide() == 0) {
                if (this->_Info.getGameIdx() == this->_Info.getGameNames().size() - 1) {
                    this->_Info.setGameIdx(0);
                    this->_Info.setScoring(this->_Info.getGameSelected().substr(0, this->_Info.getGameSelected().find_last_of('/') + 1) + getGameNameSelected() + "/Score.txt");
                } else if (this->_Info.getGameNames().size() > 1) {
                    this->_Info.setGameIdx(this->_Info.getGameIdx() + 1);
                    this->_Info.setScoring(this->_Info.getGameSelected().substr(0, this->_Info.getGameSelected().find_last_of('/') + 1) + getGameNameSelected() + "/Score.txt");
                }
            }
        } else if (tmp == ENTER) {
            if (this->_Info.getSide() == 2) {
                this->_Info.setSide(0);
            } else {
                this->GameLoop();
            }
        } else if (tmp == EXIT) {
            exit (0);
        }
        _Graphic->displayMenu(this->_Info);
    }
}