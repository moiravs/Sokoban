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

#if !defined(MYLIB_CONSTANTS_H)
#define MYLIB_CONSTANTS_H 1

// Cases
const int EMPTY = 0;
const int PLAYER = 1;
const int BOX = 2;
const int WALL = 3;
const int TELEPORTATION = 4;
const int BOX_FINAL_POS = 5;

// Main Window
const int windowWidth = 700;
const int windowHeight = 700;
const double refreshPerSecond = 60;

#endif
