/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
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
const int windowWidth = 900;
const int windowHeight = 900;
const double refreshPerSecond = 60;

//Board display
const int boardx = 200;
const int boardy = 200;
const int boardw = 600;
const int boardh = 600;

//Button reset display
const int resetx = 200;
const int resety = 620;
const int resetw = 100;
const int reseth = 25;

//PAS
const int pasx = 500;
const int pasy = 150;

// PAS
const int winorlosex = 200;
const int winorlosey = 100;

//Level button display
const int choicex = 350;
const int choicey = 620;
const int choicew = 100;
const int choiceh = 25;

// Level button display
const int helpx = 350;
const int helpy = 700;
const int helpw = 100;
const int helph = 25;

// Level button display
const int resetminpasx = 500;
const int resetminpasy = 620;
const int resetminpasw = 100;
const int resetminpash = 25;

const int limitpasx = 200;
const int limitpasy = 150;

const int minpasx = 330;
const int minpasy = 150;

//levels
const std::string level1 = "Niveaux/niveau1.txt";
const std::string level2 = "Niveaux/niveau2.txt";
const std::string level3 = "Niveaux/niveau3.txt";
const std::string level4 = "Niveaux/niveau4.txt";

//Images
const std::string imageplayer = "Textures/marioooo.png";
const std::string imagewall = "Textures/Stone_Wall.png";

#endif
