/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Allegro
*/

#ifndef ALLEGRO_HPP_
#define ALLEGRO_HPP_

#include <iostream>
#include <string>
#include "../IGraphics.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

class Allegro : public IGraphics {
    public:
        Allegro();
        ~Allegro();
        Input getInput() final;
        void displayGame(const std::vector<std::vector<char>> &tab) final;
        void displayMenu(const Info &Info) final;
        void setPreview(std::vector<std::vector<char>> &tab) final;
        void setScore(const std::string &score) final;
        void setLife(const std::string &life) final;
        void init(const std::vector<InitTab> &tab) final;
    protected:
    private:
        void InputName(const Info &Info);
        void InitColor(const Info &Info);
        void initSprites(const std::vector<std::vector<char>> &tab);
        std::string cutName(const std::string &str);
        void drawAll(const std::vector<std::vector<char>> &tab);
        const std::string &getName(void) const final;
        ALLEGRO_BITMAP * getImageAtChar(const char c) const;

        ALLEGRO_KEYBOARD_STATE _key;
        ALLEGRO_DISPLAY *_display;
        ALLEGRO_EVENT_QUEUE* q;
        ALLEGRO_EVENT_QUEUE* _queue;
        ALLEGRO_EVENT evt;
        ALLEGRO_FONT *_font;
        ALLEGRO_FONT *_fontTitle;
        ALLEGRO_FONT *_fontSubTitle;
        ALLEGRO_COLOR _colorName;
        ALLEGRO_COLOR _colorTitle[3];
        ALLEGRO_BITMAP *_background;
        ALLEGRO_TIMER*timer;

        std::string _concatScore;
        std::string _name;
        int _timerBackground; 
        std::string _life;
        std::string _score;
        int _screen;
        std::vector<InitTab> _initTab;
        std::vector<std::vector<std::pair<ALLEGRO_BITMAP *, char>>> _sprites;
        std::vector<ALLEGRO_COLOR> _colorGame;
        std::vector<ALLEGRO_COLOR> _colorGraph;
};

#endif /* !ALLEGRO_HPP_ */
