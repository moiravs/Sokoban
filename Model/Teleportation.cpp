/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "Teleportation.hpp"

LogicCell *Teleportation::getSecondEnd()
{
    return this->second_end;
}
LogicCell *Teleportation::getFirstEnd()
{
    return this->first_end;
}
bool Teleportation::isDone()
{
    return this->teleportationDone;
}