/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** InitTab
*/

#include "InitTab.hpp"

InitTab::InitTab(char c, int iC, int oC, const std::string &str)
{
    this->_c = c;
    this->_inColor = iC;
    this->_outColor = oC;
    this->_path = str;
}

InitTab::~InitTab()
{
}

char InitTab::getCharacter() const
{
    return this->_c;
}

int InitTab::getInColor() const
{
    return this->_inColor;
}

int InitTab::getOutColor() const
{
    return this->_outColor;
}
const std::string &InitTab::getPath() const
{
    return this->_path;
}
