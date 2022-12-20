
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




