
#include "ControllerBoard.hpp"
#include <fstream>

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
void ControllerBoard::reset_handle()
{
    this->boardModel->pas = 0;
    this->boardModel->endofparty = false;
    std::string aer = this->boardModel->readFileIntoString();
    this->boardModel->createBoard(aer);
}
void ControllerBoard::custom_handle()
{
}

void ControllerBoard::level_change(int choice)
{
    this->saveminpas();
    this->boardModel->endofparty = false;
    std::cout << choice << std::endl;
    switch (choice)
    {
    case -1:
        return;
    case 0:
        this->boardModel->filename = level1;
        break;
    case 1:
        puts("level2");
        this->boardModel->filename = level2;
        break;
    case 2:
        puts("level3");
        this->boardModel->filename = level3;
        break;
        
    }
    std::string buffer = this->boardModel->readFileIntoString();
    this->boardModel->createBoard(buffer);
}

void ControllerBoard::resetminpas()
{
    this->boardModel->pas = 0;
    this->boardModel->winorlose = true;
    this->saveminpas();
}

void ControllerBoard::saveminpas()
{
    if (((this->boardModel->pas < this->boardModel->minpas) && (this->boardModel->winorlose == true)) || ((this->boardModel->minpas == 0) && (this->boardModel->winorlose == true)))
    {
        std::string strReplace = "l" + std::to_string(this->boardModel->minpas);
        std::string strNew = "l" + std::to_string(this->boardModel->pas);
        std::ifstream filein(this->boardModel->filename); // File to read from
        std::ofstream fileout("fileout.txt");             // Temporary file
        if (!filein || !fileout)
        {
            std::cout << "Error opening files!" << std::endl;
        }

        std::string strTemp;
        bool found = false;
        while (filein >> strTemp)
        {
            if ((strTemp == strReplace) && (found == false))
            {
                strTemp = strNew;
                found = true;
            }
            strTemp += "\n";
            fileout << strTemp;
        }
        filein.close();
        remove(this->boardModel->filename.c_str());
        std::rename("fileout.txt", this->boardModel->filename.c_str());
    }
}