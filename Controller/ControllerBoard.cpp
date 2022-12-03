
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
    this->boardModel->endofparty = false;
    if (choice == -1)
    {
        return;
    }
    if (choice == 0)
    {
        this->boardModel->filename = level1;
    }
    else if (choice == 1)
        this->boardModel->filename = level2;
    std::string buffer = this->boardModel->readFileIntoString();
    this->boardModel->createBoard(buffer);
}

void ControllerBoard::saveminpas(){
    if (((this->boardModel->pas < this->boardModel->minpas) && (this->boardModel->winorlose == true)) || ((this->boardModel->minpas == 0) && (this->boardModel->winorlose == true))){
        //TODO: for multiple files il faut noter dans le niveau le pas max et le min pas
        std::string strReplace = std::to_string(this->boardModel->minpas);
        std::string strNew = std::to_string(this->boardModel->pas);
        std::ifstream filein(level1);   // File to read from
        std::ofstream fileout("fileout.txt"); // Temporary file
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
        remove(level1.c_str());
        std::rename("fileout.txt", level1.c_str());
    }
}