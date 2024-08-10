/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

extern "C" std::unique_ptr<IGraphics> createInterface()
{
    return std::make_unique<Ncurses>();
}

Ncurses::Ncurses()
{
    initscr();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    notimeout(stdscr, FALSE);
    curs_set(0);
    noecho();
    cbreak();
    start_color();

    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_RED);
}

Ncurses::~Ncurses()
{
    endwin();
}

void Ncurses::displayGame(const std::vector<std::vector<char>> &tab)
{
    std::string error("/ Too small window \\");

    if (getmaxx(stdscr) < tab[0].size() || getmaxy(stdscr) < tab.size() + 3) {
        mvprintw(getmaxy(stdscr) / 2, getmaxx(stdscr) / 2 - error.size() / 2, "%s", error.c_str());
    } else {
        mvprintw(1, getmaxx(stdscr) / 2 - tab[0].size() / 2, "%s", this->_life.c_str());
        mvprintw(1, getmaxx(stdscr) / 2 + tab[0].size() / 2 - this->_score.size(), "%s", this->_score.c_str());
        for (size_t idx_x = 0; idx_x < tab.size(); idx_x++) {
            for (size_t idx_y = 0; idx_y < tab[idx_x].size(); idx_y++) {
                attron(COLOR_PAIR(tab[idx_x][idx_y]));
                mvprintw(idx_x + 3, getmaxx(stdscr) / 2 - tab[idx_x].size() / 2 + idx_y, "%c", tab[idx_x][idx_y]);
                attroff(COLOR_PAIR(tab[idx_x][idx_y]));
            }
        }
    }
    refresh();
    flushinp();
}

std::string Ncurses::cutName(const std::string &str)
{
    std::string tmp(str);

    tmp = tmp.substr(tmp.find_last_of('_') + 1);
    if (tmp.find(".so") != tmp.npos) {
        tmp = tmp.substr(0, tmp.find(".so"));
    }
    return(tmp);
}

void Ncurses::displayMenu(const Info &Info)
{
    std::vector<std::string> game = Info.getGameNames();
    std::vector<std::string> graph = Info.getGraphNames();
    std::vector<Score> score = Info.getScoring();
    int key = -1;
    int padding = 0;
    std::string tmp;
    std::string arcade_str("/ Arcade \\");
    std::string games_str("-Games-");
    std::string graphs_str("-Graphics-");
    std::string name_str("/ Name \\");
    std::string score_str("/ Score \\");

    mvprintw(1, getmaxx(stdscr) / 2 - arcade_str.size() / 2, "%s", arcade_str.c_str());
    mvprintw(3, getmaxx(stdscr) / 4 - games_str.size() / 2, "%s", games_str.c_str());
    mvprintw(3, getmaxx(stdscr) - getmaxx(stdscr) / 4 - graphs_str.size() / 2, "%s", graphs_str.c_str());

    for (size_t idx = 0; idx < game.size(); idx++) {
        tmp = this->cutName(game[idx]);
        if (game[idx] == Info.getGameSelected()) {
            if (Info.getSide() == 0) {
                attron(COLOR_PAIR(2));
                mvprintw(4 + idx, getmaxx(stdscr) / 4 - tmp.size() / 2, "%s", tmp.c_str());
                attroff(COLOR_PAIR(2));
            } else {
                attron(COLOR_PAIR(1));
                mvprintw(4 + idx, getmaxx(stdscr) / 4 - tmp.size() / 2, "%s", tmp.c_str());
                attroff(COLOR_PAIR(1));
            }
        } else {
            mvprintw(4 + idx, getmaxx(stdscr) / 4 - tmp.size() / 2, "%s", tmp.c_str());
        }
    }
    for (size_t idy = 0; idy < graph.size(); idy++) {
        tmp = this->cutName(graph[idy]);
        if (graph[idy] == Info.getGraphSelected()) {
            if (Info.getSide() == 1) {
                attron(COLOR_PAIR(2));
                mvprintw(4 + idy, getmaxx(stdscr) - getmaxx(stdscr) / 4 - tmp.size() / 2, "%s", tmp.c_str());
                attroff(COLOR_PAIR(2));
            } else {
                attron(COLOR_PAIR(1));
                mvprintw(4 + idy, getmaxx(stdscr) - getmaxx(stdscr) / 4 - tmp.size() / 2, "%s", tmp.c_str());
                attroff(COLOR_PAIR(1));
            }
        } else {
            mvprintw(4 + idy, getmaxx(stdscr) - getmaxx(stdscr) / 4 - tmp.size() / 2, "%s", tmp.c_str());
        }
    }
    padding = (game.size() > graph.size()) ? game.size() : graph.size();
    mvprintw(5 + padding, getmaxx(stdscr) / 2 - name_str.size() / 2, "%s", name_str.c_str());
    if (Info.getSide() == 2) {
        key = getch();
        if (isalnum(key)) {
            this->_name += key;
        } else if (key == 263 && !this->_name.empty()) {
            this->_name.pop_back();
        }
        attron(COLOR_PAIR(1));
    }
    for (size_t idx = 0; idx < this->_name.size() + 4; idx++) {
        mvprintw(6 + padding, getmaxx(stdscr) / 2 - this->_name.size() / 2 - 2 + idx, "-");
    }
    mvprintw(7 + padding, getmaxx(stdscr) / 2 - this->_name.size() / 2 - 2, "|");
    if (this->_name.size() % 2 == 0) {
        mvprintw(7 + padding, getmaxx(stdscr) / 2 + this->_name.size() / 2 + 1, "|");
    } else {
        mvprintw(7 + padding, getmaxx(stdscr) / 2 + this->_name.size() / 2 + 2, "|");
    }
    for (size_t idx = 0; idx < this->_name.size() + 4; idx++) {
        mvprintw(8 + padding, getmaxx(stdscr) / 2 - this->_name.size() / 2 - 2 + idx, "-");
    }
    attroff(COLOR_PAIR(1));
    mvprintw(7 + padding, getmaxx(stdscr) / 2 - this->_name.size() / 2, "%s", this->_name.c_str());

    mvprintw(10 + padding, getmaxx(stdscr) / 2 - score_str.size() / 2, "%s", score_str.c_str());
    if (!score.empty()) {
        for (size_t idx = 0; idx < 7 && idx < score.size(); idx++) {
            mvprintw(11 + padding + idx, getmaxx(stdscr) / 2 - (score[idx].getName().size() + score[idx].getScore().size() + 3) / 2, "%s - %s", score[idx].getName().c_str(), score[idx].getScore().c_str());
        }
    } else {
        mvprintw(11 + padding, getmaxx(stdscr) / 2 - 7, "No High Score");
    }
    refresh();
    flushinp();
}

void Ncurses::setPreview(std::vector<std::vector<char>> &tab)
{
}

void Ncurses::init(const std::vector<InitTab> &tab)
{
    for (size_t idx = 0; idx < tab.size(); idx++) {
        init_pair(tab[idx].getCharacter(), tab[idx].getInColor(), tab[idx].getOutColor());
    }
}

void Ncurses::setScore(const std::string &score)
{
    this->_score = score;
}

void Ncurses::setLife(const std::string &life)
{
    this->_life = life;
}

Input Ncurses::getInput()
{
    int key = 0;

    clear();
    key = getch();
    if (key == 27) {
        return EXIT;
    } else if (key == 119) {
        return PREV_GRAPH;
    }  else if (key == 120) {
        return NEXT_GRAPH;
    }  else if (key == 99) {
        return PREV_GAME;
    }  else if (key == 118) {
        return NEXT_GAME;
    }  else if (key == 258 || key == 115) {
        return KEY_DOWN;
    }  else if (key == 259 || key == 122) {
        return KEY_UP;
    }  else if (key == 260 || key == 113) {
        return KEY_LEFT;
    }  else if (key == 261 || key == 100) {
        return KEY_RIGHT;
    }  else if (key == 10) {
        return ENTER;
    } else {
        return NONE;
    }
}

const std::string &Ncurses::getName(void) const
{
    return _name;
}