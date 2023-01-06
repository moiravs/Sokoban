/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "Teleportation.hpp"

std::tuple<int, int> Teleportation::getOtherEnd(int y, int x)
{
    if (y == this->firstEnd->getY() && x == this->firstEnd->getX())
        return {this->secondEnd->getY(), this->secondEnd->getX()};
    else if (y == this->secondEnd->getY() && x == this->secondEnd->getX())
        return {this->firstEnd->getY(), this->firstEnd->getX()};
    else
        return {-1, -1};
}