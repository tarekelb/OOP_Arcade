/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Allegro
*/

#include "Allegro.hpp"

extern "C" std::unique_ptr<IGraphics> createInterface()
{
    return std::make_unique<Allegro>();
}


void Allegro::setPreview(__attribute((unused))std::vector<std::vector<char>> &tab)
{
}

Allegro::Allegro()
{
    al_install_system(ALLEGRO_VERSION_INT, atexit);
    if (!al_init())
        al_show_native_message_box(NULL, "Erreur", "Error Init", "Could not initialize", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    _display = al_create_display(1920, 1080);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    _font = al_load_font("./lib/ALLEGRO/assets/Lowpoly.ttf", 50, 0);
    _fontTitle = al_load_font("./lib/ALLEGRO/assets/Deep_Shadow.ttf", 60, 0);
    _fontSubTitle = al_load_font("./lib/ALLEGRO/assets/Astro_World.ttf", 60, 0);
    if (!_display)
        al_show_native_message_box(NULL, "Erreur", "Error Display", "Could not Display", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    al_install_keyboard();
    q = al_create_event_queue();
    _queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 30);
    al_register_event_source(_queue, al_get_display_event_source(_display));
    al_register_event_source(q, al_get_keyboard_event_source());
    al_register_event_source(_queue,al_get_timer_event_source(timer));    
    al_init_image_addon();
    al_start_timer(timer);
    _timerBackground = 0;

    _colorTitle[0] = al_map_rgb(255, 0, 0);
    _colorTitle[1] = al_map_rgb(0, 255, 0);
    _colorTitle[2] = al_map_rgb(255, 128, 0);
    _colorName = al_map_rgb(50, 50, 50);

    _background = al_load_bitmap("./lib/ALLEGRO/assets/background.png");
}

Allegro::~Allegro()
{
    al_destroy_font(_font);
    al_destroy_font(_fontTitle);
    al_destroy_font(_fontSubTitle);
    al_destroy_display(_display);
}

Input Allegro::getInput()
{
    al_get_keyboard_state(&_key);

    if (al_key_down(&_key, ALLEGRO_KEY_ESCAPE))
        return EXIT;
    else if (al_key_down(&_key, ALLEGRO_KEY_W))
        return PREV_GRAPH;
    else if (al_key_down(&_key, ALLEGRO_KEY_X))
        return NEXT_GRAPH;
    else if (al_key_down(&_key, ALLEGRO_KEY_C))
        return PREV_GAME;
    else if (al_key_down(&_key, ALLEGRO_KEY_V))
        return NEXT_GAME;
    else if (al_key_down(&_key, ALLEGRO_KEY_DOWN) || al_key_down(&_key, ALLEGRO_KEY_S))
        return KEY_DOWN;
    else if (al_key_down(&_key, ALLEGRO_KEY_UP) || al_key_down(&_key, ALLEGRO_KEY_Z))
        return KEY_UP;
    else if (al_key_down(&_key, ALLEGRO_KEY_LEFT) || al_key_down(&_key, ALLEGRO_KEY_Q))
        return KEY_LEFT;
    else if (al_key_down(&_key, ALLEGRO_KEY_RIGHT) || al_key_down(&_key, ALLEGRO_KEY_D))
        return KEY_RIGHT;
    else if (al_key_down(&_key, ALLEGRO_KEY_ENTER))
        return ENTER;
    else
        return NONE;
}

const std::string &Allegro::getName(void) const
{
    return _name;
}

void Allegro::initSprites(const std::vector<std::vector<char>> &tab)
{
    std::pair<ALLEGRO_BITMAP *, char> pair;

    for (size_t a = 0; a < tab.size(); a += 1) {
        std::vector<std::pair<ALLEGRO_BITMAP *, char>> tmp;
        for (size_t c = 0; c < tab[a].size(); c += 1) {
            pair = {getImageAtChar(tab[a][c]), tab[a][c]};
            tmp.push_back(pair);
        }
        _sprites.push_back(tmp);
    }
    _screen = (1920 - (tab[0].size() * al_get_bitmap_width(_sprites[0][0].first))) / 2;
}

void Allegro::InitColor(const Info &Info)
{
     if (this->_colorGraph.empty() || this->_colorGraph.empty()) {
        for (size_t a = 0; a < Info.getGraphNames().size(); a += 1) {
            if (Info.getSide() == 1)
                _colorGraph.push_back(al_map_rgb(50, 55, 55));
            else
                _colorGraph.push_back(al_map_rgb(255, 255, 255));
        }
        for (size_t a = 0; a < Info.getGameNames().size(); a += 1) {
            if (Info.getSide() == 0)
                _colorGame.push_back(al_map_rgb(50, 55, 55));
            else
                _colorGame.push_back(al_map_rgb(255, 255, 255));
        }
    }
}

void Allegro::drawAll(const std::vector<std::vector<char>> &tab)
{
    std::pair<ALLEGRO_BITMAP *, char> pair;

    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(_font, al_map_rgb(255, 0, 255), this->_screen + 100, 20, ALLEGRO_ALIGN_LEFT, _life.c_str());
    al_draw_text(_font, al_map_rgb(255, 0, 255), this->_screen + (tab[0].size() * al_get_bitmap_width(_sprites[0][0].first)) - 100, 20, ALLEGRO_ALIGN_RIGHT, _score.c_str());

    for (size_t a = 0; a < tab.size(); a += 1) {
        for (size_t b = 0; b < tab[a].size(); b += 1) {
            if (_sprites[a][b].second != tab[a][b]) {
                al_destroy_bitmap(_sprites[a][b].first);
                pair = {getImageAtChar(tab[a][b]), tab[a][b]};
                _sprites[a][b] = pair;
            }
            if (_sprites[a][b].second != ' ')
                al_draw_bitmap(_sprites[a][b].first, _screen + (b * al_get_bitmap_width(_sprites[a][b].first)), (a * al_get_bitmap_width(_sprites[a][b].first)) + 100, 0);
        }
    }
    al_flip_display();
}

void Allegro::displayGame(const std::vector<std::vector<char>> &tab)
{
    if (_sprites.empty())
        initSprites(tab);
    drawAll(tab);
}

ALLEGRO_BITMAP *Allegro::getImageAtChar(const char c) const
{
    for (size_t a = 0; a < _initTab.size(); a += 1) {
        if (_initTab[a].getCharacter() == c)
            return al_load_bitmap(_initTab[a].getPath().c_str());
    }
    return nullptr;
}

std::string Allegro::cutName(const std::string &str)
{
    std::string tmp(str);

    tmp = tmp.substr(tmp.find_last_of('_') + 1);
    if (tmp.find(".so") != tmp.npos) {
        tmp = tmp.substr(0, tmp.find(".so"));
    }
    return(tmp);
}

void Allegro::InputName(const Info &Info)
{
    if (Info.getSide() == 2) {
        _colorName = al_map_rgb(255, 255, 255);

        al_wait_for_event_timed(q, &evt, 1.0/ 10);
        if ((evt.type == ALLEGRO_EVENT_KEY_CHAR && evt.keyboard.unichar != 8 && isalnum(evt.keyboard.unichar) && _name.size() <= 15) || \
        (evt.type == ALLEGRO_EVENT_KEY_CHAR && evt.keyboard.unichar == 32)) {
            _name += evt.keyboard.unichar;
        } else if (evt.type == ALLEGRO_EVENT_KEY_CHAR && evt.keyboard.unichar == 8 && _name.size())
            _name.pop_back();
    } else
        _colorName = al_map_rgb(50, 50, 50);
}

void Allegro::displayMenu(const Info &Info)
{
    InitColor(Info);
    al_clear_to_color(al_map_rgb(0,0,0));
    ALLEGRO_EVENT event;
    al_wait_for_event(_queue, &event);
    if (event.type == ALLEGRO_EVENT_TIMER) {
        if (_timerBackground <= -1920)
            _timerBackground = 0;
        _timerBackground --;
    }
    al_draw_bitmap(_background, _timerBackground, 0, 0);
    al_draw_text(_fontTitle, _colorTitle[rand() % 3], (1920 / 2) - (60 * 4), 30, 0, "ARCADE");
    al_draw_text(_fontSubTitle, al_map_rgb(0, 45, 255), ((1920 / 6) - 30), 250, 0, "GAMES");
    al_draw_text(_fontSubTitle, al_map_rgb(0, 45, 255), ((1920 / 5 * 2) - 30), 250 , 0, "LIBRARY");
    al_draw_text(_fontSubTitle, al_map_rgb(0, 45, 255), (1920 / 5 * 3) + 80, 250, 0,  "ENTER YOUR NAME");
    al_draw_text(_fontSubTitle, al_map_rgb(0, 45, 255), (1920 / 5 * 3) + 80, 500, 0,  "HIGH SCORES");

    for (size_t a = 0; a < Info.getGameNames().size(); a += 1) {
        if (Info.getSide() == 0 && a != Info.getGameIdx())
            _colorGame[a] = al_map_rgb(255, 255, 255);
        else if (a == Info.getGameIdx() && Info.getSide() == 0)
            _colorGame[Info.getGameIdx()] = al_map_rgb(255, 0, 0);
        else if (a == Info.getGameIdx() && Info.getSide() != 0)
            _colorGame[Info.getGameIdx()] = al_map_rgb(128, 0, 0);
        else
            _colorGame[a] = al_map_rgb(50, 50, 50);
        al_draw_text(_font, _colorGame[a], (1920 / 6), 350 + 80 * a, 0, cutName(Info.getGameNames()[a]).c_str());
    }
    for (size_t a = 0; a < Info.getGraphNames().size(); a += 1) {
        if (Info.getSide() == 1 && a != Info.getGraphIdx())
            _colorGraph[a] = al_map_rgb(255, 255, 255);
        else if (a == Info.getGraphIdx() && Info.getSide() == 1)
            _colorGraph[Info.getGraphIdx()] = al_map_rgb(255, 0, 0);
        else if (a == Info.getGraphIdx() && Info.getSide() != 1)
            _colorGraph[Info.getGraphIdx()] = al_map_rgb(128, 0, 0);
        else
            _colorGraph[a] = al_map_rgb(50, 50, 50);
        al_draw_text(_font, _colorGraph[a], (1920 / 5 * 2), 350 + 80 * a, 0, cutName(Info.getGraphNames()[a]).c_str());
    }
    InputName(Info);
    al_draw_filled_rectangle((1920 / 5 * 3) + 80, 350, (1920 / 5 * 3) + 550, 440, _colorName);
    al_draw_text(_font, al_map_rgb(0, 0, 0), (1920 / 5 * 3) + 85, 380, 0, _name.c_str());
    if (Info.getScoring().size()) {
        size_t size = Info.getScoring().size() > 7 ? 7 : Info.getScoring().size();
        for (size_t i = 0; i < size; i ++) {
            _concatScore = Info.getScoring()[i].getName() + " - " + Info.getScoring()[i].getScore();
            al_draw_text(_font, al_map_rgb(255, 255, 255), (1920 / 5 * 3) + 85, 580 + 50 * i, 0, _concatScore.c_str());
        }
    } else
        al_draw_text(_font, al_map_rgb(255, 255, 255), (1920 / 5 * 3) + 85, 580, 0, "No High Score");
    al_flip_display();
}

void Allegro::setScore(const std::string &score)
{
    this->_score = score;
}

void Allegro::setLife(const std::string &life)
{
    this->_life = life;
}

void Allegro::init(const std::vector<InitTab> &tab)
{
    if (!_initTab.empty()) {
        _sprites.clear();
    }
    _initTab = tab;
}