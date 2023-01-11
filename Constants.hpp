/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */

#ifndef __CONSTANTS_HPP
#define __CONSTANTS_HPP

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Menu_Bar.H>

#include <vector>
#include <iostream>
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
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;
const double REFRESH_PER_SECOND = 60;

// Board display
const int BOARD_X = 200;
const int BOARD_Y = 200;
const int BOARD_W = 600;
const int BOARD_H = 600;

// Button reset display
const int RESET_X = 200;
const int RESET_Y = 620;
const int RESET_W = 100;
const int RESET_H = 25;

// PAS
const int PAS_X = 500;
const int PAS_Y = 150;

// PAS
const int PARTY_WON_X = 200;
const int PARTY_WON_Y = 100;

// Level button display
const int CHOICE_X = 350;
const int CHOICE_Y = 620;
const int CHOICE_W = 100;
const int CHOICE_H = 25;

// Level button display
const int HELP_X = 350;
const int HELP_Y = 700;
const int HELP_W = 100;
const int HELP_H = 25;

// Level button display
const int RESET_BEST_SCORE_X = 500;
const int RESET_BEST_SCORE_Y = 620;
const int RESET_BEST_SCORE_W = 100;
const int RESET_BEST_SCORE_H = 25;

const int STEPS_LIMIT_X = 200;
const int STEPS_LIMIT_Y = 150;

const int MIN_STEPS_X = 330;
const int MIN_STEPS_Y = 150;

// levels
const std::string LEVEL1 = "Niveaux/niveau1.txt";
const std::string LEVEL2 = "Niveaux/niveau2.txt";
const std::string LEVEL3 = "Niveaux/niveau3.txt";
const std::string LEVEL4 = "Niveaux/niveau4.txt";

// Images
const std::string PLAYER_IMAGE = "Textures/Mario.png";
const std::string WALL_IMAGE = "Textures/Stone_Wall.png";

const int LEVEL_W = 100;
const int LEVEL_H = 100;

const int LEVEL1_X = 100;
const int LEVEL1_Y = 100;
const int LEVEL2_X = 100;
const int LEVEL2_Y = 250;
const int LEVEL3_X = 250;
const int LEVEL3_Y = 100;
const int LEVEL4_X = 250;
const int LEVEL4_Y = 250;

const int HELP_W_X = 400;
const int HELP_W_Y = 400;
const int HELP_W_W = 400;
const int HELP_W_H = 400;

#endif
