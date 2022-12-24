/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "LogicCell.hpp"

class Teleportation;

class Teleportation
{
    LogicCell *firstEnd;
    LogicCell *secondEnd;
    size_t line, column;

public:
    Teleportation(){};
    std::tuple<int, int> getOtherEnd(int x, int y);
    void setFirstEnd(LogicCell *firstEnd) { this->firstEnd = firstEnd; }
    void setSecondEnd(LogicCell *secondEnd) { this->secondEnd = secondEnd; }
};