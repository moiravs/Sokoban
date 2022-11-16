#ifndef __CONSTANTS_HPP
#define __CONSTANTS_HPP
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <string>
#include <math.h>

#include <time.h>
#include <chrono>
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



// Cases
const int EMPTY = 0;
const int PLAYER = 1;
const int BOX = 2;
const int WALL = 3;
const int TELEPORTATION = 4;
const int BOX_FINAL_POS = 5;

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
const int resety = 10;
const int resetw = 40;
const int reseth = 25;


#endif
