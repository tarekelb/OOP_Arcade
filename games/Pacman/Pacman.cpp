/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#include "Pacman.hpp"

extern "C" { std::shared_ptr<IGames> createInterface()
    {
        return std::make_shared<Pacman>();
    }
}

Pacman::Pacman()
{
    std::string life("3");
    std::string score("0");

    std::srand(time(NULL));
    this->_speed = 0.6;
    this->generateInit();
    this->generateMap("./games/Pacman/map/map01");
    this->generateMonster();
    this->_way = NONE;
    this->_life = life;
    this->_score = score;
    this->_super = 0;
    this->_player = {this->_respawnPac.first, this->_respawnPac.second};
}

Pacman::~Pacman()
{
}

const float &Pacman::getSpeed(void) const
{
    return this->_speed;
}

void Pacman::generateInit()
{
    InitTab wall('#', 1, 1, "games/Pacman/assets/Wall.png");
    InitTab gum('.', 2, 2, "games/Pacman/assets/Gum.png");
    InitTab supergum(':', 2, 2, "games/Pacman/assets/SuperGum.png");
    InitTab pacman('^', 3, 3, "games/Pacman/assets/Pacman_up.png");
    InitTab pacman1('v', 3, 3, "games/Pacman/assets/Pacman_down.png");
    InitTab pacman2('<', 3, 3, "games/Pacman/assets/Pacman_left.png");
    InitTab pacman3('>', 3, 3, "games/Pacman/assets/Pacman_right.png");
    InitTab blinky('$', 4, 4, "games/Pacman/assets/Blinky_left.png");
    InitTab blinky1('=', 4, 4, "games/Pacman/assets/Blinky_right.png");
    InitTab pinky('@', 4, 4, "games/Pacman/assets/Pinky_left.png");
    InitTab pinky1('+', 4, 4, "games/Pacman/assets/Pinky_right.png");
    InitTab inky('%', 4, 4, "games/Pacman/assets/Inky_left.png");
    InitTab inky1('-', 4, 4, "games/Pacman/assets/Inky_right.png");
    InitTab clyde('&', 4, 4, "games/Pacman/assets/Clyde_left.png");
    InitTab clyde1('*', 4, 4, "games/Pacman/assets/Clyde_right.png");
    InitTab ghost('~', 5, 5, "games/Pacman/assets/Ghost.png");

    this->_init.push_back(wall);
    this->_init.push_back(gum);
    this->_init.push_back(supergum);
    this->_init.push_back(pacman);
    this->_init.push_back(pacman1);
    this->_init.push_back(pacman2);
    this->_init.push_back(pacman3);
    this->_init.push_back(blinky);
    this->_init.push_back(pinky);
    this->_init.push_back(inky);
    this->_init.push_back(clyde);
    this->_init.push_back(blinky1);
    this->_init.push_back(pinky1);
    this->_init.push_back(inky1);
    this->_init.push_back(clyde1);
    this->_init.push_back(ghost);
}

void Pacman::generateMap(std::string name)
{
    std::fstream file(name);
    std::string data;
    size_t idx_x = 0;

    if (file.is_open()) {
        while (std::getline(file, data)) {
            std::vector<char> tmp;
            for (size_t idx_y = 0; idx_y < data.size(); idx_y++) {
                if (data[idx_y] == '&') {
                    this->_respawnGhost = {idx_x, idx_y};
                    tmp.push_back(' ');
                } else if (data[idx_y] == 'C') {
                    this->_respawnPac = {idx_x, idx_y};
                    tmp.push_back(' ');
                } else {
                    tmp.push_back(data[idx_y]);
                }
            }
            this->_map.push_back(tmp);
            this->_stock.push_back(tmp);
            idx_x++;
        }
    } else {
        std::cerr << "MAP NOT FOUND" << std::endl;
        exit(84);
    }
    file.close();
}

void Pacman::generateMonster()
{
    Ghost Blinky(this->_respawnGhost.first, this->_respawnGhost.second, 30, '$', '=');
    Ghost Pinky(this->_respawnGhost.first, this->_respawnGhost.second, 60, '@', '+');
    Ghost Inky(this->_respawnGhost.first, this->_respawnGhost.second, 90, '%', '-');
    Ghost Clyde(this->_respawnGhost.first, this->_respawnGhost.second, 120, '&', '*');

    this->_ghosts.push_back(Blinky);
    this->_ghosts.push_back(Pinky);
    this->_ghosts.push_back(Inky);
    this->_ghosts.push_back(Clyde);
}

void Pacman::checkInput(Input key)
{
    if (key != NONE) {
        if (key == KEY_UP && this->_map[this->_player.first - 1][this->_player.second] != '#') {
            this->_way = key;
        } else if (key == KEY_DOWN && this->_map[this->_player.first + 1][this->_player.second] != '#') {
            this->_way = key;
        } else if (key == KEY_LEFT && this->_map[this->_player.first][this->_player.second - 1] != '#') {
            this->_way = key;
        } else if (key == KEY_RIGHT && this->_map[this->_player.first][this->_player.second + 1] != '#') {
            this->_way = key;
        }
    }
}

void Pacman::superGum()
{
    for (size_t idx = 0; idx < this->_ghosts.size(); idx++) {
        if (this->_ghosts[idx].getRespawn() == 0) {
            this->_ghosts[idx].setActive(false);
        }
    }
    this->_super = 25 + (this->_speed * 5);
}

void Pacman::movePacman()
{
    if (this->_stock[this->_player.first][this->_player.second] == '$' || this->_stock[this->_player.first][this->_player.second] == '@' || this->_stock[this->_player.first][this->_player.second] == '%' || this->_stock[this->_player.first][this->_player.second] == '&') {
        this->_life = std::to_string(std::stoi(this->_life) - 1);
        this->reset();
        return;
    } else if (this->_stock[this->_player.first][this->_player.second] == '~') {
        for (size_t idx = 0; idx < this->_ghosts.size(); idx++) {
            if (this->_player.first == this->_ghosts[idx].getPos().first && this->_player.second == this->_ghosts[idx].getPos().second) {
                this->_ghosts[idx].killGhost();
                this->_score = std::to_string(std::stoi(this->_score) + 500);
            }
        }
    }
    if (this->_super == 0) {
        for (size_t idx = 0; idx < this->_ghosts.size(); idx++) {
            this->_ghosts[idx].setActive(true);
        }
    } else {
        this->_super--;
    }
    if (this->_way == KEY_UP) {
        if (this->_player.first == 0) {
            this->_player.first = this->_map.size() - 1;
        } else if (this->_stock[this->_player.first - 1][this->_player.second] == ' ') {
            this->_player.first--;
        } else if (this->_stock[this->_player.first - 1][this->_player.second] == '.') {
            this->_player.first--;
            this->_score = std::to_string(std::stoi(this->_score) + 50);
            this->_map[this->_player.first][this->_player.second] = ' ';
        } else if (this->_stock[this->_player.first - 1][this->_player.second] == ':') {
            this->_player.first--;
            this->_map[this->_player.first][this->_player.second] = ' ';
            this->_score = std::to_string(std::stoi(this->_score) + 200);
            this->superGum();
        } else if (this->_stock[this->_player.first - 1][this->_player.second] == '#') {

        }
    } else if (this->_way == KEY_DOWN) {
        if (this->_player.first == this->_map.size() - 1) {
            this->_player.first = 0;
        } else if (this->_stock[this->_player.first + 1][this->_player.second] == ' ') {
            this->_player.first++;
        } else if (this->_stock[this->_player.first + 1][this->_player.second] == '.') {
            this->_player.first++;
            this->_map[this->_player.first][this->_player.second] = ' ';
            this->_score = std::to_string(std::stoi(this->_score) + 50);
        } else if (this->_stock[this->_player.first + 1][this->_player.second] == ':') {
            this->_player.first++;
            this->_map[this->_player.first][this->_player.second] = ' ';
            this->_score = std::to_string(std::stoi(this->_score) + 200);
            this->superGum();
        } else if (this->_stock[this->_player.first + 1][this->_player.second] == '#') {
            
        }
    } else if (this->_way == KEY_LEFT) {
        if (this->_player.second == 0) {
            this->_player.second = this->_map[this->_player.first].size() - 1;
        } else if (this->_stock[this->_player.first][this->_player.second - 1] == ' ') {
            this->_player.second--;
        } else if (this->_stock[this->_player.first][this->_player.second - 1] == '.') {
            this->_player.second--;
            this->_map[this->_player.first][this->_player.second] = ' ';
            this->_score = std::to_string(std::stoi(this->_score) + 50);
        } else if (this->_stock[this->_player.first][this->_player.second - 1] == ':') {
            this->_player.second--;
            this->_map[this->_player.first][this->_player.second] = ' ';
            this->_score = std::to_string(std::stoi(this->_score) + 200);
            this->superGum();
        } else if (this->_stock[this->_player.first][this->_player.second - 1] == '#') {
            
        }
    } else if (this->_way == KEY_RIGHT) {
        if (this->_player.second == this->_map[this->_player.first].size() - 1) {
            this->_player.second = 0;
        } else if (this->_stock[this->_player.first][this->_player.second + 1] == ' ') {
            this->_player.second++;
        } else if (this->_stock[this->_player.first][this->_player.second + 1] == '.') {
            this->_player.second++;
            this->_map[this->_player.first][this->_player.second] = ' ';
            this->_score = std::to_string(std::stoi(this->_score) + 50);
        } else if (this->_stock[this->_player.first][this->_player.second + 1] == ':') {
            this->_player.second++;
            this->_map[this->_player.first][this->_player.second] = ' ';
            this->_score = std::to_string(std::stoi(this->_score) + 200);
            this->superGum();
        } else if (this->_stock[this->_player.first][this->_player.second + 1] == '#') {
            
        }
    }
}

void Pacman::reset()
{
    this->_way = NONE;
    this->_player = {this->_respawnPac.first, this->_respawnPac.second};
    for (size_t idx = 0; idx < this->_ghosts.size(); idx++) {
        this->_ghosts[idx].setPos(this->_respawnGhost.first, this->_respawnGhost.second);
        this->_ghosts[idx].setRespawn(30 * (idx + 1));
    }
}

void Pacman::checkEnd()
{
    for (size_t idx_x = 0; idx_x < this->_map.size(); idx_x++) {
        for (size_t idx_y = 0; idx_y < this->_map[idx_x].size(); idx_y++) {
            if (this->_map[idx_x][idx_y] == '.') {
                return;
            }
        }
    }
    this->_map.clear();
    this->_stock.clear();
    this->generateMap("./games/Pacman/map/map01");
    this->reset();
    this->_speed += this->_speed / 5;
}

const std::vector<std::vector<char>> &Pacman::simulate(Input key)
{
    this->checkInput(key);
    this->copyMap();
    for (size_t idx = 0; idx < this->_ghosts.size(); idx++) {
        this->_ghosts[idx].moveGhost(this->_stock);
    }
    this->movePacman();
    this->fillMap();
    this->checkEnd();
    return this->_stock;
}

void Pacman::copyMap()
{
    for (size_t idx_x = 0; idx_x < this->_map.size(); idx_x++) {
        for (size_t idx_y = 0; idx_y < this->_map[idx_x].size(); idx_y++) {
            this->_stock[idx_x][idx_y] = this->_map[idx_x][idx_y];
        }
    }
}

void Pacman::fillMap()
{
    if (this->_way == KEY_UP) {
        this->_stock[this->_player.first][this->_player.second] = '^';
    } else if (this->_way == KEY_DOWN) {
        this->_stock[this->_player.first][this->_player.second] = 'v';
    } else if (this->_way == KEY_RIGHT) {
        this->_stock[this->_player.first][this->_player.second] = '>';
    } else {
        this->_stock[this->_player.first][this->_player.second] = '<';
    }
}

const std::string &Pacman::getScore() const
{
    return this->_score;
}

const std::string &Pacman::getLife() const
{
    return this->_life;
}

const std::vector<InitTab> &Pacman::getInit() const
{
    return this->_init;
}
