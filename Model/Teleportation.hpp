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

public:
    // Constructors
    Teleportation(){};

    // Setters
    void setFirstEnd(LogicCell *firstEnd) { this->firstEnd = firstEnd; }
    void setSecondEnd(LogicCell *secondEnd) { this->secondEnd = secondEnd; }

    // Methods
    /**
     * @brief  Getter for the other end of the teleportation
     * @param  x: position X of the player
     * @param  y: position Y of the player
     * @retval tuple of the other end, {-1,-1} if the player is not on a teleportation case
     */
    std::tuple<int, int> getOtherEnd(int y, int x);
};