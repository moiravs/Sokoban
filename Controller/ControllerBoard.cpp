
#include "ControllerBoard.hpp"

int ControllerBoard::board_handle(int event)
{
    if (Fl::event_key() == FL_Up)
    {
        if (boardModel->move(boardModel->player->getY() - 1, boardModel->player->getX()))
            this->boardModel->pas += 1;
    }
    else if (Fl::event_key() == FL_Down)
    {
        if (boardModel->move(boardModel->player->getY() + 1, boardModel->player->getX()))
            this->boardModel->pas += 1;
    }
    else if (Fl::event_key() == FL_Right)
    {
        if (boardModel->move(boardModel->player->getY(), boardModel->player->getX() + 1))
            this->boardModel->pas += 1;
    }
    else if (Fl::event_key() == FL_Left)
    {
        if (boardModel->move(boardModel->player->getY(), boardModel->player->getX() - 1))
            this->boardModel->pas += 1;
    }
    else if (Fl::event_key(97))
    {
        boardModel->teleport();
    }

    if ((this->boardModel->pas == this->boardModel->limitpas) || (this->boardModel->isFailure()))
    {
        this->boardModel->endofparty = true;
        this->boardModel->winorlose = false;
    }

    if (boardModel->end_of_party())
    {
        this->boardModel->endofparty = true;
        this->boardModel->winorlose = true;
    }
    return 1;
}

void ControllerBoard::move_to(int x, int y)
{
    int player_x = this->boardModel->player->getX();
    int player_y = this->boardModel->player->getY();
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
                this->boardModel->LogicCellVector[this->boardModel->player->getY()][this->boardModel->player->getX()]->setPlayer(nullptr);
                this->boardModel->LogicCellVector[player_y + deplacement][player_x]->setPlayer(this->boardModel->player);
                this->boardModel->player->setY(player_y + deplacement);
                this->boardModel->player->setX(player_x);
                player_x = this->boardModel->player->getX();
                player_y = this->boardModel->player->getY();
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
                this->boardModel->pas +=1;
                this->boardModel->LogicCellVector[this->boardModel->player->getY()][this->boardModel->player->getX()]->setPlayer(nullptr);
                this->boardModel->LogicCellVector[player_y][player_x + deplacement]->setPlayer(this->boardModel->player);
                this->boardModel->player->setY(player_y);
                this->boardModel->player->setX(player_x + deplacement);
                player_x = this->boardModel->player->getX();
                player_y = this->boardModel->player->getY();
            }
        }
    }
}
