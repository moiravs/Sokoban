
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
#include <stdio.h>  // fprintf()
#include <stdlib.h> // exit()
#include <string.h> // strcmp()

#include <FL/Fl_Menu_Bar.H>

#if !defined(MYLIB_CONSTANTS_H)
#define MYLIB_CONSTANTS_H 1

// Cases
const int WALL = 3;
const int BOX = 2;

// Main Window

const int windowWidth = 700;
const int windowHeight = 700;
const double refreshPerSecond = 60;

#endif