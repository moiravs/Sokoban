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
    LogicCell * first_end;
    LogicCell *second_end;
    bool other_end_blocked;
    bool teleportation_done = false;
    size_t line, column;

public:
    Teleportation(LogicCell * first_end): first_end{first_end}{};
    LogicCell *get_second_end();
    LogicCell *get_first_end();
    bool is_done();
    void set_second_end(LogicCell *second_end){
        this->second_end = second_end;
    }
};