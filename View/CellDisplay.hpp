/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
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

class Cell
{
    Point center;
    int type;
    int w, h;
    Fl_PNG_Image *personnage;
    Fl_PNG_Image *wall;
    Fl_Color fillColor, frameColor;
    int color;

public:
    // Constructors
    Cell(Point center, int type, int w, int h, int color);
    ~Cell();

    // Getters and Setters
    Point getCenter() { return center; } // Source : Programmation Language Course

    // Methods
    /**
     * @brief  draw the Cell
     * @retval None
     */
    void draw();
    /**
     * @brief  Check if the cell contains the mouseLoc
     * @param  mouseLoc: the mouse location
     * @retval true if the mouse location is in the cell
     */
    bool mouseClick(Point mouseLoc);
};

#endif