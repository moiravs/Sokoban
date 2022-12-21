/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "ControllerBoard.hpp"



void ControllerBoard::move_to(int x, int y)
{
    int player_x = this->boardModel->player->x;
    int player_y = this->boardModel->player->y;
    if (x == player_x)
    {
        int deplacement;
        if (y > player_y)
            deplacement = 1;
        else if (y < player_y)
            deplacement = -1;
        if (y != player_y)
        {
            while (!this->boardModel->LogicCellVector[player_y + deplacement][player_x]->hasBox() && player_y != y)
            {
                this->boardModel->pas += 1;
                this->boardModel->LogicCellVector[this->boardModel->player->y][this->boardModel->player->x]->setPlayer(nullptr);
                this->boardModel->LogicCellVector[player_y + deplacement][player_x]->setPlayer(this->boardModel->player);
                this->boardModel->player->y = player_y + deplacement;
                this->boardModel->player->x = player_x;
                player_x = this->boardModel->player->x;
                player_y = this->boardModel->player->y;
            }
        }
    }
    else if (y == player_y)
    {
        int deplacement;
        if (x > player_x)
            deplacement = 1;
        else if (x < player_x)
            deplacement = -1;
        if (x != player_x)
        {
            while (!this->boardModel->LogicCellVector[player_y][player_x + deplacement]->hasBox() && player_x != x)
            {
                this->boardModel->pas += 1;
                this->boardModel->LogicCellVector[this->boardModel->player->y][this->boardModel->player->x]->setPlayer(nullptr);
                this->boardModel->LogicCellVector[player_y][player_x + deplacement]->setPlayer(this->boardModel->player);
                this->boardModel->player->y = player_y;
                this->boardModel->player->x = player_x + deplacement;
                player_x = this->boardModel->player->x;
                player_y = this->boardModel->player->y;
            }
        }
    }
}
