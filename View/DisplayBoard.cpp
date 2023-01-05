/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef DISPLAYBOARD_CPP
#define DISPLAYBOARD_CPP

#include "DisplayBoard.hpp"

void DisplayBoard::draw() // Source : Programmation Language Course
{
    for (auto &c : cells)
        c.draw();
}

std::tuple<int, int> DisplayBoard::mouseClick(Point mouseLoc) // Source : Programmation Language Course
{
    for (size_t i = 0; i < (boardModel->getLogicCellVector().size() * boardModel->getLogicCellVector()[0].size()) - 1; i++)
    {
        if (cells[i].mouseClick(mouseLoc))
            return std::tuple<int, int>(i / boardModel->getLogicCellVector().size(), i % boardModel->getLogicCellVector()[0].size());
    }
    throw("Unexpected Error: Problem with mouseClick");
}

void DisplayBoard::update()
{
    cells.clear();
    for (size_t y = 0; y < boardModel->getLogicCellVector().size(); y++)
    {
        for (size_t x = 0; x < boardModel->getLogicCellVector()[0].size(); x++)
        {
            if (boardModel->getLogicCellVector()[y][x]->hasPlayer())
                cells.push_back(Cell{Point{BOARD_X + 50 * ((int)x % 20), BOARD_Y + 50 * ((int)y)}, PLAYER, 50, 50, FL_WHITE});
            else if (boardModel->getLogicCellVector()[y][x]->hasBox())
                cells.push_back(Cell{Point{BOARD_X + 50 * ((int)x % 20), BOARD_Y + 50 * ((int)y)}, BOX, 50, 50, boardModel->getLogicCellVector()[y][x]->getBox()->color});
            else if (boardModel->getLogicCellVector()[y][x]->getType() == BOX_FINAL_POS)
                cells.push_back(Cell{Point{BOARD_X + 50 * ((int)x % 20), BOARD_Y + 50 * ((int)y)}, BOX_FINAL_POS, 50, 50, boardModel->getLogicCellVector()[y][x]->getColor()});
            else
            {
                cells.push_back(Cell{Point{BOARD_X + 50 * ((int)x % 20), BOARD_Y + 50 * ((int)y)}, boardModel->getLogicCellVector()[y][x]->getType(), 50, 50, FL_BLACK});
            }
        }
    }
}

#endif