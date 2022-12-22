/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef BOX_HPP
#define BOX_HPP
#include "../Constants.hpp"
class Box
{
    int x;
    int y;
    int color;
    bool light = false;
    bool blocked = false;

public:
    Box(int x, int y) : x{x}, y{y}{}
    int getColor(){
        return this->color;
    }
    void setColor(int color){
        this->color = color;
    }
    void setLight(bool light){
        this->light = true;
        this->color = FL_LIGHT1;
    }
    bool getLight(){
        return this->light;
    }
    void setBlocked(bool blocked){
        this->blocked = true;
    }
    bool getBlocked(){
        return this->blocked;
    }
};
#endif