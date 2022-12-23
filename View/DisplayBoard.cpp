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
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 20), boardy + 50 * ((int)y)}, PLAYER, 50, 50, FL_WHITE});
            else if (boardmodel->getLogicCellVector()[y][x]->hasBox())
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 20), boardy + 50 * ((int)y)}, BOX, 50, 50, boardmodel->getLogicCellVector()[y][x]->getBox()->color});
            else if (boardmodel->getLogicCellVector()[y][x]->getType() == BOX_FINAL_POS)
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 20), boardy + 50 * ((int)y)}, BOX_FINAL_POS, 50, 50, boardmodel->getLogicCellVector()[y][x]->getColor()});
            else
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 20), boardy + 50 * ((int)y)}, boardmodel->getLogicCellVector()[y][x]->getType(), 50, 50, FL_BLACK});
        }
    }
}

#endif