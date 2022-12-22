/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef CELLDISPLAY_HPP
#define CELLDISPLAY_HPP
#include "../Constants.hpp"
struct Point
{
    int x, y;
};


class BoxDisplay
{
    Point center;
    int w, h;
    Fl_PNG_Image *wall;

public:
    BoxDisplay(Point center, int w, int h);
    void draw();
};

class PlayerDisplay
{
    Point center;
    int w, h;
    Fl_JPEG_Image *personnage;

public:
    PlayerDisplay(Point center, int w, int h);
    void draw();
};

class Cell 
{
    bool on = false;
    Point center;
    int type;
    int w, h;
    Fl_Color fillColor, frameColor;
    PlayerDisplay *personnage;
    BoxDisplay *box;
    int color;

public:
    Cell(Point center, int type, int w, int h, int color);
    void draw();
    bool contains(Point p) ;
    Point getCenter(){ return center; }
    bool mouseClick(Point mouseLoc);
};

#endif