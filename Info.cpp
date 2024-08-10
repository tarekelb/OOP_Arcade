/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Info
*/

#include "Info.hpp"

Info::Info(const std::string &lib)
{
    this->_gameIdx = 0;
    this->_side = 0;
    this->setListNames("./games/", this->_gameNames);
    this->setListNames("./lib/", this->_graphNames);
    std::vector<std::string>::iterator index = std::find(_graphNames.begin(), _graphNames.end(), lib);

    if (index != _graphNames.end()) {
        this->_graphIdx = std::distance(_graphNames.begin(), std::find(_graphNames.begin(), _graphNames.end(), lib));
    } else {
        exit(84);
    }
}

void Info::setListNames(const std::string &path, std::vector<std::string> &list)
{
    DIR *dirp = opendir(path.c_str());
    struct dirent *dp;

    while ((dp = readdir(dirp)) != NULL) {
        if (dp->d_name[0] != '.') {
            if ((path + dp->d_name).find(".so") != path.npos) {
                list.push_back(path + dp->d_name);
            }
        }
    }
    closedir(dirp);
}

Info::~Info()
{
}

struct less_than_score
{
    inline bool operator() (const Score &score1, const Score &score2)
    {
        return (std::stoi(score1.getScore()) > std::stoi(score2.getScore()));
    }
};

void Info::addScore(const Score &score)
{
    std::fstream stream;

    this->_scoring.push_back(score);

    std::sort(this->_scoring.begin(), this->_scoring.end(), less_than_score());
    std::string tmp = this->_gameNames[this->_gameIdx].substr(this->_gameNames[this->_gameIdx].find_last_of('_') + 1);
    tmp[0] = std::toupper(tmp[0]);
    tmp = tmp.substr(0, tmp.find('.'));

    stream.open(getGameSelected().substr(0, getGameSelected().find_last_of('/') + 1) + tmp + "/Score.txt", std::ios::out);
    if (stream.is_open()) {
        for (size_t i = 0; i < _scoring.size(); i += 1) {
            stream << _scoring[i].getName() + ":" + _scoring[i].getScore() + "\n";
        }
    }
    stream.close();
}

const std::vector<Score> &Info::getScoring() const
{
    return this->_scoring;
}

void Info::setScoring(const std::string &file)
{
    std::fstream stream;
    _scoring.clear();

    stream.open(file);
    if (stream.is_open()) {
        std::string buf;
        while (std::getline(stream, buf))
            _scoring.push_back(Score(buf.substr(0, buf.find(':')), buf.substr(buf.find(':') + 1)));
    }
    stream.close();
}

void Info::setGraphIdx(const size_t &idx)
{
    this->_graphIdx = idx;
}

void Info::setGameIdx(const size_t &idx)
{
    this->_gameIdx = idx;
}

void Info::setSide(const size_t &side)
{
    this->_side = side;
}

size_t Info::getGraphIdx() const
{
    return this->_graphIdx;
}

size_t Info::getGameIdx() const
{
    return this->_gameIdx;
}

size_t Info::getSide() const
{
    return this->_side;
}

const std::vector<std::string> &Info::getGraphNames() const
{
    return this->_graphNames;
}

const std::vector<std::string> &Info::getGameNames() const
{
    return this->_gameNames;
}

const std::string &Info::getGameSelected() const
{
    return this->_gameNames[this->_gameIdx];
}

const std::string &Info::getGraphSelected() const
{
    return this->_graphNames[this->_graphIdx];
}
