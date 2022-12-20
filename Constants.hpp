#ifndef __CONSTANTS_HPP
#define __CONSTANTS_HPP
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <string>
#include <math.h>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>

#include <time.h>
#include <chrono>
#include <stdlib.h>
#include <vector>

#include <iostream>
#include <random>
#include <array>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Menu_Bar.H>
#include <memory>
#include <string>
#include <unistd.h>
#include <fstream>

// Cases
const int EMPTY = 0;
const int PLAYER = 1;
const int BOX = 2;
const int WALL = 3;
const int TELEPORTATION = 4;
const int BOX_FINAL_POS = 5;
const int LIGHT_BOX = 6;

const char BLUE_BOX = 'A';
const char BLUE_BOX_FINAL_POS = 'B';
const char RED_BOX = 'C';
const char RED_BOX_FINAL_POS = 'D';

// Main Window
const int windowWidth = 900;
const int windowHeight = 900;
const double refreshPerSecond = 60;

//Board display
const int boardx = 100;
const int boardy = 100;
const int boardw = 600;
const int boardh = 600;

//Button reset display
const int resetx = 10;
const int resety = 115;
const int resetw = 75;
const int reseth = 25;

// Button reset display
const int customx = 10;
const int customy = 120;
const int customw = 40;
const int customh = 25;

const int pasx = 600;
const int pasy = 80;
const int pasw = 80;
const int pash = 25;

//Level button display
const int choicex = 60;
const int choicey = 50;
const int choicew = 100;
const int choiceh = 25;

// Level button display
const int resetminpasx = 400;
const int resetminpasy = 50;
const int resetminpasw = 100;
const int resetminpash = 25;

const int limitpasx = 700;
const int limitpasy = 80;

//levels
const std::string level1 = "Niveaux/niveau1.txt";
const std::string level2 = "Niveaux/niveau2.txt";
const std::string level3 = "Niveaux/niveau3.txt";

//Images
const std::string imageplayer = "Textures/Test.jpeg";
const std::string imagewall = "Textures/wall.png";

#endif
