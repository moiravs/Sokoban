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
    LogicCell *second_end;
    size_t line, column;

public:
    Teleportation()
    {};
    LogicCell *getSecondEnd();
    LogicCell *getFirstEnd();
    void setFirstEnd(LogicCell *firstEnd)
    {
        this->firstEnd= firstEnd;
    }
    void setSecondEnd(LogicCell *second_end)
    {
        this->second_end = second_end;
    }
};