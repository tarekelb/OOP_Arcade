/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../IGraphics.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SFML : public IGraphics {
    public:
        SFML();
        ~SFML();
        Input getInput() final;
        const std::string &getName(void) const final;
        void displayGame(const std::vector<std::vector<char>> &tab) final;
        void displayMenu(const Info &Info) final;
        void setPreview(std::vector<std::vector<char>> &tab) final;
        void setScore(const std::string &score) final;
        void setLife(const std::string &life) final;
        void init(const std::vector<InitTab> &tab) final;

    protected:
    private:
        sf::Sprite linkTextures(const char c) const;
        std::string cutName(const std::string &str);
        bool changeGame(const Info &Info);
        void InputName(const Info &Info);

        std::vector<sf::Text *> _text_game;
        std::vector<sf::Text *> _text_lib;
        std::vector<sf::Text *> _text_score;
        std::vector<sf::Texture *> _textures;
        std::vector<std::vector<std::pair<sf::Sprite, char>>> _sprites;
        std::vector<InitTab> _tab;
        sf::Event event;
        sf::RenderWindow *_window;
        sf::Text *_tscore;
        sf::Text *_tlife;
        sf::Text *_tmarcade;
        sf::Text *_tmscore;
        sf::Text *_tmname;
        sf::Text *_tmgames;
        sf::Text *_tmlib;
        sf::Text *_hscore;
        sf::Text *_text_name;
        sf::Font _font;
        std::string _concatScore;
        std::string _name;
        sf::RectangleShape rect;
        float _screen;
        int _spriteSize;
};

#endif /* !SFML_HPP_ */
