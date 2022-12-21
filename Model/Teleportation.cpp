/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "Teleportation.hpp"

LogicCell * Teleportation::get_second_end()
{
    return this->second_end;
}
LogicCell *Teleportation::get_first_end()
{
    return this->first_end;
}
bool Teleportation::is_done()
{
    return this->teleportation_done;
}