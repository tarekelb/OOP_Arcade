/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SFML
*/

#include "SFML.hpp"
#include <unistd.h>

extern "C" { std::unique_ptr<SFML> createInterface()
    {
        return std::make_unique<SFML>();
    }
}

void SFML::setPreview(std::vector<std::vector<char>> &tab)
{
}

const std::string &SFML::getName(void) const
{
    return this->_name;
}

void SFML::init(const std::vector<InitTab> &tab)
{
    this->_tab = tab;
    sf::Texture *tmp;
    sf::Sprite spr;

    if (this->_textures.empty() == false) {
        this->_textures.clear();
    }
    for (size_t i = 0; i < tab.size(); i++) {
        tmp = new sf::Texture;
        tmp->loadFromFile(this->_tab[i].getPath());
        this->_textures.push_back(tmp);
    }
    spr.setTexture(*tmp);
    this->_spriteSize = spr.getLocalBounds().width;
}

Input SFML::getInput()
{
    while (this->_window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            this->_window->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        return EXIT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        return PREV_GRAPH;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        return NEXT_GRAPH;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        return PREV_GAME;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
        return NEXT_GAME;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        return KEY_DOWN;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        return KEY_UP;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        return KEY_LEFT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        return KEY_RIGHT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        return ENTER;
    } else {
        return NONE;
    }
}

void SFML::displayGame(const std::vector<std::vector<char>> &tab)
{
    std::pair<sf::Sprite, char> pair;

    if (!this->_window->isOpen()) {
        return;
    }
    if (this->_sprites.empty()) {
        this->_screen = (1920 - (tab[0].size() * this->_spriteSize)) / 2;
        this->_tlife->setPosition({this->_screen + 100, 20});
        this->_tscore->setPosition({this->_screen + (tab[0].size() * this->_spriteSize) - 100, 20});
        for (size_t a = 0; a < tab.size(); a += 1) {
            std::vector<std::pair<sf::Sprite, char>> tmp;
            for (size_t c = 0; c < tab[a].size(); c += 1) {
                    pair = {this->linkTextures(tab[a][c]), tab[a][c]};
                    pair.first.setPosition({this->_screen + (c * 20), 100 + (a * 20)});
                    tmp.push_back(pair);
                }
            this->_sprites.push_back(tmp);
        }
    }
    this->_window->clear();
    for (size_t a = 0; a < tab.size(); a += 1) {
        for (size_t c = 0; c < tab[a].size(); c += 1) {
            if (this->_sprites[a][c].second != tab[a][c]) {
                this->_sprites[a][c].second = tab[a][c];
                this->_sprites[a][c].first = this->linkTextures(tab[a][c]);
                this->_sprites[a][c].first.setPosition({this->_screen + (c * 20), 100 + (a * 20)});
            }
            if (_sprites[a][c].second != ' ') {
                this->_window->draw(this->_sprites[a][c].first);
            }
        }
    }
    if (this->_tlife != NULL && this->_tscore != NULL) {
        this->_window->draw(*this->_tlife);
        this->_window->draw(*this->_tscore);
    }
    this->_window->display();
}

sf::Sprite SFML::linkTextures(const char c) const
{
    sf::Sprite spr;

    for (size_t i = 0; i < this->_tab.size(); i++) {
        if (this->_tab[i].getCharacter() == c) {
            spr.setTexture(*this->_textures[i], false);
            return (spr);
        }
    }
    return spr;
}

std::string SFML::cutName(const std::string &str)
{
    std::string tmp(str);

    tmp = tmp.substr(tmp.find_last_of('_') + 1);
    if (tmp.find(".so") != tmp.npos) {
        tmp = tmp.substr(0, tmp.find(".so"));
    }
    return(tmp);
}

bool SFML::changeGame(const Info &Info)
{
    if (this->_text_score.size() != Info.getScoring().size()) {
        return true;
    }
    for (size_t i = 0; i < this->_text_score.size(); i++) {
        if (this->_text_score[i]->getString() != Info.getScoring()[i].getName() + " - " + Info.getScoring()[i].getScore()) {
            return true;
        }
    }
    return false;
}

void SFML::InputName(const Info &Info)
{
    if (Info.getSide() == 2) {
        this->_text_name->setColor(sf::Color(0, 0, 0));
        this->rect.setFillColor(sf::Color(255, 255, 255));
        if (this->event.type == sf::Event::TextEntered && this->event.text.unicode == 8 && this->_name.size() >= 1) {
            this->_name.pop_back();
        }
        if (this->event.type == sf::Event::TextEntered && this->_name.size() < 8 && isalnum(this->event.text.unicode)) {
            this->_name += this->event.text.unicode;
        }
        this->_text_name->setString(this->_name);
        this->_window->draw(this->rect);
        this->_window->draw(*this->_text_name);
    } else {
        return;
    }
}

void SFML::displayMenu(const Info &Info)
{
    if (!this->_window->isOpen()) {
        return;
    }
    if (this->_text_game.empty() || this->_text_lib.empty()) {
        for (size_t i = 0; i != Info.getGameNames().size(); i++) {
            this->_text_game.push_back(new sf::Text);
            this->_text_game[i]->setFont(this->_font);
            this->_text_game[i]->setCharacterSize(60);
            this->_text_game[i]->setString(cutName(Info.getGameNames()[i]));
            this->_text_game[i]->setOrigin({this->_text_game[i]->getLocalBounds().width / 2, 0});
            this->_text_game[i]->setPosition({(1920 / 6) + 60, 350 + 80 * i});
        }
        for (size_t i = 0; i != Info.getGraphNames().size(); i++) {
            this->_text_lib.push_back(new sf::Text);
            this->_text_lib[i]->setFont(this->_font);
            this->_text_lib[i]->setCharacterSize(60);
            this->_text_lib[i]->setString(cutName(Info.getGraphNames()[i]));
            this->_text_lib[i]->setOrigin({this->_text_lib[i]->getLocalBounds().width / 2, 0});
            this->_text_lib[i]->setPosition({((1920 / 5 * 2) + 85), 350 + 80 * i});
        }
    }
    this->_window->clear();
    this->rect.setPosition({(1920 / 5 * 3) + 80, 380});
    this->_window->draw(*this->_tmarcade);
    this->_window->draw(*this->_tmgames);
    this->_window->draw(*this->_tmlib);
    this->_window->draw(*this->_tmname);
    this->_window->draw(*this->_tmscore);
    this->rect.setFillColor(sf::Color(128, 128, 128));
    this->_text_name->setColor(sf::Color(0, 0, 0));
    this->_window->draw(this->rect);
    this->_window->draw(*this->_text_name);
    InputName(Info);
    if (Info.getScoring().size() || this->changeGame(Info) == false) {
        size_t size = Info.getScoring().size() > 7 ? 7 : Info.getScoring().size();
        for (size_t i = 0; i < size; i++) {
            this->_text_score.push_back(new sf::Text);
            this->_text_score[i]->setFont(this->_font);
            this->_text_score[i]->setCharacterSize(60);
            this->_concatScore = Info.getScoring()[i].getName() + " - " + Info.getScoring()[i].getScore();
            this->_text_score[i]->setString(this->_concatScore);
            this->_text_score[i]->setPosition({(1920 / 5 * 3) + 85, 580 + 50 * i});
        }
    }
    if (!Info.getScoring().empty() && !this->_text_score.empty()) {
        size_t size = (Info.getScoring().size() > 7) ? 7 : Info.getScoring().size();
        for (size_t i = 0; i < size; i++) {
            this->_window->draw(*this->_text_score[i]);
        }
    } else {
        this->_window->draw(*this->_hscore);
    }
    for (size_t i = 0; i != this->_text_game.size(); i++) {
        if (this->_text_game[i]->getString() == cutName(Info.getGameSelected())) {
            if (Info.getSide() == 0) {
                this->_text_game[i]->setColor(sf::Color(255, 0, 0));
            } else {
                this->_text_game[i]->setColor(sf::Color(128, 0, 0));
            }
        } else {
            if (Info.getSide() == 0) {
                this->_text_game[i]->setColor(sf::Color(255, 255, 255));
            } else {
                this->_text_game[i]->setColor(sf::Color(128, 128, 128));
            }
        }
        this->_window->draw(*this->_text_game[i]);
    }
    for (size_t i = 0; i != this->_text_lib.size(); i++) {
        if (this->_text_lib[i]->getString() == cutName(Info.getGraphSelected())) {
            if (Info.getSide() == 1) {
                this->_text_lib[i]->setColor(sf::Color(255, 0, 0));
            } else {
                this->_text_lib[i]->setColor(sf::Color(128, 0, 0));
            }
        } else {
            if (Info.getSide() == 1) {
                this->_text_lib[i]->setColor(sf::Color(255, 255, 255));
            } else {
                this->_text_lib[i]->setColor(sf::Color(128, 128, 128));
            }
        }
        this->_window->draw(*this->_text_lib[i]);
    }
    this->_window->display();
}

void SFML::setScore(const std::string &score)
{
    if (this->_tscore != NULL) {
        this->_tscore->setString(score);
        this->_tscore->setOrigin({this->_tscore->getLocalBounds().width, 0});
    }
}

void SFML::setLife(const std::string &life)
{
    if (this->_tlife != NULL) {
        this->_tlife->setString(life);
    }
}

SFML::SFML()
{
    sf::VideoMode mode;
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    mode = (sf::VideoMode){1920, 1080, 32};
    this->_tlife = new sf::Text;
    this->_tscore = new sf::Text;
    this->_tmarcade = new sf::Text;
    this->_tmlib = new sf::Text;
    this->_hscore = new sf::Text;
    this->_tmgames = new sf::Text;
    this->_tmscore = new sf::Text;
    this->_tmname = new sf::Text;
    this->_text_name = new sf::Text;

    this->rect.setFillColor(sf::Color(128, 128, 128));
    this->rect.setSize({440, 80});
    this->_window = new sf::RenderWindow(modes[0], "SFML", sf::Style::Fullscreen);
    this->_window->setMouseCursorVisible(false);
    this->_font.loadFromFile("lib/SFML/assets/Lowpoly.ttf");
    this->_tlife->setFont(this->_font);
    this->_tscore->setFont(this->_font);
    this->_tmarcade->setFont(this->_font);
    this->_tmgames->setFont(this->_font);
    this->_tmlib->setFont(this->_font);
    this->_tmname->setFont(this->_font);
    this->_tmscore->setFont(this->_font);
    this->_hscore->setFont(this->_font);
    this->_text_name->setFont(this->_font);
    this->_tlife->setCharacterSize(60);
    this->_tscore->setCharacterSize(60);
    this->_tmarcade->setCharacterSize(60);
    this->_tmlib->setCharacterSize(60);
    this->_tmname->setCharacterSize(60);
    this->_tmscore->setCharacterSize(60);
    this->_tmgames->setCharacterSize(60);
    this->_hscore->setCharacterSize(60);
    this->_text_name->setCharacterSize(60);
    this->_tlife->setString(std::to_string(0));
    this->_tscore->setString(std::to_string(0));
    this->_tmarcade->setString(std::to_string(0));
    this->_tmarcade->setString("ARCADE");
    this->_tmgames->setString("GAMES");
    this->_tmlib->setString("LIBRARY");
    this->_tmname->setString("ENTER YOUR NAME");
    this->_tmscore->setString("HIGHEST SCORE");
    this->_hscore->setString("No High Score");
    this->_text_name->setPosition({(1920 / 5 * 3) + 85, 380});
    this->_tmarcade->setOrigin({this->_tmarcade->getLocalBounds().width, 0});
    this->_hscore->setPosition({(1920 / 5 * 3) + 85, 580});
    this->_tmarcade->setPosition({1920 / 2, 0});
    this->_tmgames->setPosition({((1920 / 6) - 30), 250});
    this->_tmlib->setPosition({((1920 / 5 * 2) - 30), 250});
    this->_tmname->setPosition({((1920 / 5 * 3) + 80), 250});
    this->_tmscore->setPosition({((1920 / 5 * 3) + 80), 500});
}

SFML::~SFML()
{
    this->_window->close();
}