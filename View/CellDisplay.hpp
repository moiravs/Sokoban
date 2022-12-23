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

class Cell 
{
    bool on = false;
    Point center;
    int type;
    int w, h;
    Fl_PNG_Image *personnage;
    Fl_PNG_Image *wall;
    Fl_Color fillColor, frameColor;
    int color;

public:
    Cell(Point center, int type, int w, int h, int color);
    /**
     * @brief  
     * @note   
     * @retval None
     */
    void draw();
    /**
     * @brief  
     * @note   
     * @param  p: 
     * @retval 
     */
    bool contains(Point p) ;
    /**
     * @brief  
     * @note   
     * @retval 
     */
    Point getCenter(){ return center; }
    /**
     * @brief  
     * @note   
     * @param  mouseLoc: 
     * @retval 
     */
    bool mouseClick(Point mouseLoc);
};

#endif