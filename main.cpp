/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <csignal>
#include <memory>
#include "Core.hpp"
#include <unistd.h>

void usage()
{
    printf("Usage:\t[First Argument] [Second Argument]\n\t[First Argument]\t./arcade\n\t[Second Argument]\t./lib_arcade_[Library Name]\n\nExample:");
    printf("   ./arcade ./lib_arcade_SFML.so\n\nLibrary available:\n\t- SFML\n\t- NDK++\n\t- Allegro4 / Allegro5\n");
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;

    Core core(av[1]);
    core.MainLoop();
}