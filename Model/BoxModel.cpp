/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef BOX_CPP
#define BOX_CPP
#include "BoxModel.hpp"

void Box::setX(int x)
{
    this->x = x;
}
void Box::setY(int y)
{
    this->y = y;
}
int Box::getX()
{
    return (this->x);
}
int Box::getY()
{
    return (this->y);
}
bool Box::operator==(const Box &box) const
{
return x == box.x && y == box.y;

}
#endif