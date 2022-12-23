/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef BOX_HPP
#define BOX_HPP
#include "../Constants.hpp"
struct Box
{
    int color = FL_WHITE;
    bool light = false;
    bool blocked = false;
};
#endif