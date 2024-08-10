/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** nibbler
*/

#include "Nibbler.hpp"

extern "C" { std::unique_ptr<IGames> createInterface()
    {
        return std::make_unique<Nibbler>();
    }
}

Nibbler::Nibbler()
{
    std::string life("100000");
    std::string score("0");

    std::srand(time(NULL));
    this->generateInit();
    this->_speed = 1;
    this->_life = life;
    this->_score = score;
    this->_respawn = 0;
    this->_respawn_max = 60;
    this->_way = NONE;
    this->generateMap("./games/Nibbler/map/map01");
    this->generateApple();
    this->createSnake();
}

Nibbler::~Nibbler()
{
}

const float &Nibbler::getSpeed(void) const
{
    return this->_speed;
}

void Nibbler::createSnake()
{
    std::pair<size_t, size_t> pos(this->_map.size() / 2, this->_map[0].size() / 2);
    std::pair<size_t, size_t> pos1(this->_map.size() / 2 - 1, this->_map[0].size() / 2);
    std::pair<size_t, size_t> pos2(this->_map.size() / 2 - 2, this->_map[0].size() / 2);
    std::pair<size_t, size_t> pos3(this->_map.size() / 2 - 3, this->_map[0].size() / 2);

    this->_snake.push_back(pos);
    this->_snake.push_back(pos1);
    this->_snake.push_back(pos2);
    this->_snake.push_back(pos3);
}

const std::vector<std::vector<char>> &Nibbler::simulate(Input key)
{
    if (key != NONE) {
        if (key == KEY_UP && this->_way != KEY_DOWN) {
            this->_way = key;
        } else if (key == KEY_DOWN && this->_way != KEY_UP && this->_way != NONE) {
            this->_way = key;
        } else if (key == KEY_LEFT && this->_way != KEY_RIGHT) {
            this->_way = key;
        } else if (key == KEY_RIGHT && this->_way != KEY_LEFT) {
            this->_way = key;
        }
    }
    if (this->_respawn >= this->_respawn_max) {
        this->generateApple();
    } else {
        this->_respawn++;
    }
    this->movenibbler();
    this->copyMap();
    this->fillMap();
    return this->_stock;
}

const std::string &Nibbler::getScore() const
{
    return this->_score;
}

const std::string &Nibbler::getLife() const
{
    return this->_life;
}

const std::vector<InitTab> &Nibbler::getInit() const
{
    return this->_init;
}

void Nibbler::generateMap(std::string name)
{
    std::fstream file(name);
    std::string data;
    size_t idx_x = 0;

    if (file.is_open()) {
        while (std::getline(file, data)) {
            std::vector<char> tmp;
            for (size_t idx_y = 0; idx_y < data.size(); idx_y++) {
                if (rand() % 70 == 1) {
                    tmp.push_back('#');
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

void Nibbler::copyMap(void)
{
    for (size_t idx_x = 0; idx_x < this->_map.size(); idx_x++) {
        for (size_t idx_y = 0; idx_y < this->_map[idx_x].size(); idx_y++) {
            this->_stock[idx_x][idx_y] = this->_map[idx_x][idx_y];
        }
    }
}

void Nibbler::fillMap(void)
{
    if (this->_snake[0].first > this->_snake[1].first) {
        this->_stock[this->_snake[0].first][this->_snake[0].second] = 'a';
    } else if (this->_snake[0].first < this->_snake[1].first) {
        this->_stock[this->_snake[0].first][this->_snake[0].second] = 'b';
    } else if (this->_snake[0].second > this->_snake[1].second) {
        this->_stock[this->_snake[0].first][this->_snake[0].second] = 'c';
    } else {
        this->_stock[this->_snake[0].first][this->_snake[0].second] = 'd';
    }
    for (size_t idx = 1; idx < this->_snake.size() - 1; idx++) {
        if ((this->_snake[idx].first > this->_snake[idx + 1].first && this->_snake[idx - 1].first > this->_snake[idx].first) || (this->_snake[idx].first < this->_snake[idx + 1].first && this->_snake[idx - 1].first < this->_snake[idx].first)) {
            this->_stock[this->_snake[idx].first][this->_snake[idx].second] = 'y';
        } else if ((this->_snake[idx].second > this->_snake[idx + 1].second && this->_snake[idx - 1].second > this->_snake[idx].second) || (this->_snake[idx].second < this->_snake[idx + 1].second && this->_snake[idx - 1].second < this->_snake[idx].second)) {
            this->_stock[this->_snake[idx].first][this->_snake[idx].second] = 'z';
        } else if ((this->_snake[idx].second > this->_snake[idx - 1].second && this->_snake[idx].first > this->_snake[idx + 1].first) || (this->_snake[idx].second > this->_snake[idx + 1].second && this->_snake[idx].first > this->_snake[idx - 1].first)) {
            this->_stock[this->_snake[idx].first][this->_snake[idx].second] = 'm';
        } else if ((this->_snake[idx].second < this->_snake[idx + 1].second && this->_snake[idx].first > this->_snake[idx - 1].first) || (this->_snake[idx].second < this->_snake[idx - 1].second && this->_snake[idx].first > this->_snake[idx + 1].first)) {
            this->_stock[this->_snake[idx].first][this->_snake[idx].second] = 'p';
        } else if ((this->_snake[idx].second < this->_snake[idx + 1].second && this->_snake[idx].first < this->_snake[idx - 1].first) || (this->_snake[idx].second < this->_snake[idx - 1].second && this->_snake[idx].first < this->_snake[idx + 1].first)) {
            this->_stock[this->_snake[idx].first][this->_snake[idx].second] = 'n';
        } else if ((this->_snake[idx].second > this->_snake[idx + 1].second && this->_snake[idx].first < this->_snake[idx - 1].first) || (this->_snake[idx].second > this->_snake[idx - 1].second && this->_snake[idx].first < this->_snake[idx + 1].first)) {
            this->_stock[this->_snake[idx].first][this->_snake[idx].second] = 'o';
        }
    }
    if (this->_way == KEY_DOWN) {
        this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second] = 'v';
    } else if (this->_way == KEY_LEFT) {
        this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second] = '<';
    } else if (this->_way == KEY_RIGHT) {
        this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second] = '>';
    } else {
        this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second] = '^';
    }
    if (this->_respawn >= this->_respawn_max / 1.5) {
        this->_stock[this->_apple.first][this->_apple.second] = '&';
    } else if (this->_respawn >= this->_respawn_max / 3){
        this->_stock[this->_apple.first][this->_apple.second] = '%';
    } else {
        this->_stock[this->_apple.first][this->_apple.second] = '@';
    }
}

void Nibbler::generateInit(void)
{
    InitTab wall('#', 1, 1, "./games/Nibbler/assets/Wall.png");
    InitTab appleRed('@', 4, 4, "./games/Nibbler/assets/Apple_red.png");
    InitTab appleOrange('%', 4, 4, "./games/Nibbler/assets/Apple_orange.png");
    InitTab appleYellow('&', 4, 4, "./games/Nibbler/assets/Apple_yellow.png");
    InitTab snakeHead('^', 2, 2, "./games/Nibbler/assets/Snake_head_up.png");
    InitTab snakeHead1('v', 2, 2, "./games/Nibbler/assets/Snake_head_down.png");
    InitTab snakeHead2('<', 2, 2, "./games/Nibbler/assets/Snake_head_left.png");
    InitTab snakeHead3('>', 2, 2, "./games/Nibbler/assets/Snake_head_right.png");
    InitTab snakeTail('a', 3, 3, "./games/Nibbler/assets/Snake_tail_up.png");
    InitTab snakeTail1('b', 3, 3, "./games/Nibbler/assets/Snake_tail_down.png");
    InitTab snakeTail2('c', 3, 3, "./games/Nibbler/assets/Snake_tail_left.png");
    InitTab snakeTail3('d', 3, 3, "./games/Nibbler/assets/Snake_tail_right.png");
    InitTab snakeAngle('m', 3, 3, "./games/Nibbler/assets/Snake_angle_up.png");
    InitTab snakeAngle1('n', 3, 3, "./games/Nibbler/assets/Snake_angle_down.png");
    InitTab snakeAngle2('o', 3, 3, "./games/Nibbler/assets/Snake_angle_left.png");
    InitTab snakeAngle3('p', 3, 3, "./games/Nibbler/assets/Snake_angle_right.png");
    InitTab snakeBody('z', 3, 3, "./games/Nibbler/assets/Snake_body_width.png");
    InitTab snakeBody1('y', 3, 3, "./games/Nibbler/assets/Snake_body_length.png");

    this->_init.push_back(wall);
    this->_init.push_back(appleRed);
    this->_init.push_back(appleOrange);
    this->_init.push_back(appleYellow);
    this->_init.push_back(snakeAngle);
    this->_init.push_back(snakeAngle1);
    this->_init.push_back(snakeAngle2);
    this->_init.push_back(snakeAngle3);
    this->_init.push_back(snakeBody);
    this->_init.push_back(snakeBody1);
    this->_init.push_back(snakeHead);
    this->_init.push_back(snakeHead1);
    this->_init.push_back(snakeHead2);
    this->_init.push_back(snakeHead3);
    this->_init.push_back(snakeTail);
    this->_init.push_back(snakeTail1);
    this->_init.push_back(snakeTail2);
    this->_init.push_back(snakeTail3);
}

void Nibbler::movenibbler(void)
{
    std::pair<size_t, size_t> head(this->_snake[this->_snake.size() - 1].first, this->_snake[this->_snake.size() - 1].second);

    if (this->_way == KEY_UP) {
        head.first--;
        if (this->_stock[this->_snake[this->_snake.size() - 1].first - 1][this->_snake[this->_snake.size() - 1].second] != ' ' && this->_stock[this->_snake[this->_snake.size() - 1].first - 1][this->_snake[this->_snake.size() - 1].second] != '@' && this->_stock[this->_snake[this->_snake.size() - 1].first - 1][this->_snake[this->_snake.size() - 1].second] != '%' && this->_stock[this->_snake[this->_snake.size() - 1].first - 1][this->_snake[this->_snake.size() - 1].second] != '&') {
            this->getDamage();
        } else if (this->_stock[this->_snake[this->_snake.size() - 1].first - 1][this->_snake[this->_snake.size() - 1].second] == '@' || this->_stock[this->_snake[this->_snake.size() - 1].first - 1][this->_snake[this->_snake.size() - 1].second] == '%' || this->_stock[this->_snake[this->_snake.size() - 1].first - 1][this->_snake[this->_snake.size() - 1].second] == '&') {
            this->_snake.push_back(head);
            this->generateApple();
            this->_speed += this->_speed / 100;
            this->_score = std::to_string(std::stoi(this->_score) + 500 + (this->_snake.size() - 4) * (this->_snake.size() - 4));
        } else {
            this->_snake.push_back(head);
            this->_snake.erase(this->_snake.begin());
        }
    } else if (this->_way == KEY_DOWN) {
        head.first++;
        if (this->_stock[this->_snake[this->_snake.size() - 1].first + 1][this->_snake[this->_snake.size() - 1].second] != ' ' && this->_stock[this->_snake[this->_snake.size() - 1].first + 1][this->_snake[this->_snake.size() - 1].second] != '@' && this->_stock[this->_snake[this->_snake.size() - 1].first + 1][this->_snake[this->_snake.size() - 1].second] != '%' && this->_stock[this->_snake[this->_snake.size() - 1].first + 1][this->_snake[this->_snake.size() - 1].second] != '&') {
            this->getDamage();
        } else if (this->_stock[this->_snake[this->_snake.size() - 1].first + 1][this->_snake[this->_snake.size() - 1].second] == '@' || this->_stock[this->_snake[this->_snake.size() - 1].first + 1][this->_snake[this->_snake.size() - 1].second] == '%' || this->_stock[this->_snake[this->_snake.size() - 1].first + 1][this->_snake[this->_snake.size() - 1].second] == '&') {
            this->_snake.push_back(head);
            this->generateApple();
            this->_speed += this->_speed / 100;
            this->_score = std::to_string(std::stoi(this->_score) + 500 + (this->_snake.size() - 4) * (this->_snake.size() - 4));
        } else {
            this->_snake.push_back(head);
            this->_snake.erase(this->_snake.begin());
        }
    } else if (this->_way == KEY_LEFT) {
        head.second--;
        if (this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second - 1] != ' ' && this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second - 1] != '@' && this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second - 1] != '%' && this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second - 1] != '&') {
            this->getDamage();
        } else if (this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second - 1] == '@' || this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second - 1] == '%' || this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second - 1] == '&') {
            this->_snake.push_back(head);
            this->generateApple();
            this->_speed += this->_speed / 100;
            this->_score = std::to_string(std::stoi(this->_score) + 500 + (this->_snake.size() - 4) * (this->_snake.size() - 4));
        } else {
            this->_snake.push_back(head);
            this->_snake.erase(this->_snake.begin());
        }
    } else if (this->_way == KEY_RIGHT) {
        head.second++;
        if (this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second + 1] != ' ' && this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second + 1] != '@' && this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second + 1] != '%' && this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second + 1] != '&') {
            this->getDamage();
        } else if (this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second + 1] == '@' || this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second + 1] == '%' || this->_stock[this->_snake[this->_snake.size() - 1].first][this->_snake[this->_snake.size() - 1].second + 1] == '&') {
            this->_snake.push_back(head);
            this->generateApple();
            this->_speed += this->_speed / 100;
            this->_score = std::to_string(std::stoi(this->_score) + 500 + (this->_snake.size() - 4) * (this->_snake.size() - 4));
        } else {
            this->_snake.push_back(head);
            this->_snake.erase(this->_snake.begin());
        }
    }
}

void Nibbler::generateApple(void)
{
    size_t idx = 0;

    this->_respawn = 0;
    for (; idx < 1000; idx++) {
        this->_apple.first = 1 + (std::rand() % ((this->_stock.size() - 1) - 1 + 1));
        this->_apple.second = 1 + (std::rand() % ((this->_stock[0].size() - 1) - 1 + 1));
        if (this->_stock[this->_apple.first][this->_apple.second] == ' ') {
            break;
        }
    }
    if (idx == 1000) {

    }
}

void Nibbler::getDamage(void)
{
    this->_life = std::to_string(std::stoi(this->_life) - 1);
    this->generateApple();
    this->_way = NONE;
    this->_speed = 1;
    this->_snake.clear();
    this->createSnake();
}
