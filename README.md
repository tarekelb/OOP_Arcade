# OOP_arcade_2019

It's an Epitech Academic project realised in 1 month 
This projet is realised in C++ by Tarek El-Bouhali, Manuel Llamas and Tom Treboulou.

It dynamically loads and runs games using dynamic libraries (.so) for graphics SFML, Allegro, and ncurses graphics libraries. The system is designed to be generic, allowing seamless switching between these libraries during gameplay.

# Prerequisites

To run this projet you need to install :


- SFML library
```sudo apt-get install libsfml-dev libsfml-doc```

- Allegro library
```sudo apt-get install liballegro5-dev allegro5-doc codeblocks g++ xterm gdb```

- Ncurse library
```sudo apt-get install libncurses5-dev```

# Usage

To launch this project you need to run :

- ```./arcade ./lib/lib_arcade_sfml.so``` to launch the SFML library
- ```./arcade ./lib/lib_arcade_allegro.so``` to launch the Allegro library
- ```./arcade ./lib/lib_arcade_ncurse.so``` to launch the Ncurse library

During gameplay you can press either "W" of "X" to swap between the 3 graphics library