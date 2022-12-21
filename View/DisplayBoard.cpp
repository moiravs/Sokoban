/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef DISPLAYBOARD_CPP
#define DISPLAYBOARD_CPP

#include "DisplayBoard.hpp"

void DisplayBoard::draw()
{
    for (auto &c : cells)
        c.draw();

}

std::tuple<int, int> DisplayBoard::mouseClick(Point mouseLoc)
{
    for (size_t i = 0; i < 63; i++)
    {
        if (cells[i].mouseClick(mouseLoc))
            return std::tuple<int, int>(i / boardmodel->getLogicCellVector().size(), i % boardmodel->getLogicCellVector()[0].size());
    }
}

DisplayBoard::DisplayBoard(std::shared_ptr<BoardModel> board) : Fl_Box(boardx, boardy, boardw, boardh) 
{
    this->boardmodel = board;
    this->update();
}


void DisplayBoard::update()
{
    cells.clear();
    for (size_t y = 0; y < boardmodel->getLogicCellVector().size(); y++)
    {
        for (size_t x = 0; x < boardmodel->getLogicCellVector()[y].size(); x++)
        {
            if (boardmodel->getLogicCellVector()[y][x]->hasPlayer())
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, PLAYER, 50, 50, FL_BLACK});
            else if (boardmodel->getLogicCellVector()[y][x]->hasBox())
            {
                if (boardmodel->getLogicCellVector()[y][x]->getBox()->getLight() == false)
                    cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, BOX, 50, 50, boardmodel->getLogicCellVector()[y][x]->getBox()->getColor()});
                else if (boardmodel->getLogicCellVector()[y][x]->getBox()->getLight() == true)
                    cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, LIGHT_BOX, 50, 50, FL_DARK_BLUE});
            }
            else if (boardmodel->getLogicCellVector()[y][x]->getType() == WALL)
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, WALL, 50, 50, FL_DARK_YELLOW});
            else if (boardmodel->getLogicCellVector()[y][x]->getType() == BOX_FINAL_POS)
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, BOX_FINAL_POS, 50, 50, boardmodel->getLogicCellVector()[y][x]->getColor()});
            else if (boardmodel->getLogicCellVector()[y][x]->getType() == EMPTY)
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, EMPTY, 50, 50, FL_BLACK});
            else if (boardmodel->getLogicCellVector()[y][x]->getType() == TELEPORTATION)
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, TELEPORTATION, 50, 50, FL_DARK_GREEN});
            else
                std::cout << "type doesn't exists" << std::endl;
        }
    }
}

#endif