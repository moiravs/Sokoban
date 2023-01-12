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
    for (auto i : cells)
        for (auto j : i)
            j->draw();
}

std::tuple<int, int> DisplayBoard::mouseClick(Point mouseLoc) // Source : Programmation Language Course
{
    for (size_t y = 0; y < cells.size(); y++)
    {
        for (size_t x = 0; x < cells[0].size(); x++)
        {
            if (cells[y][x]->mouseClick(mouseLoc))
                return std::tuple<int, int>(y, x);
        }
    }
    return std::tuple<int, int>(-1, -1);
}

void DisplayBoard::update()
{
    for (auto i : cells)
        for (auto j : i)
            delete j;
    cells.clear();
    std::vector <Cell*> line;
    for (size_t y = 0; y < boardModel->getLogicCellVector().size(); y++)
    {
        for (size_t x = 0; x < boardModel->getLogicCellVector()[0].size(); x++)
        {
            if (boardModel->getLogicCellVector()[y][x]->hasPlayer())
            {
                Cell *cell = new Cell(Point{BOARD_X + 50 * (static_cast<int>(x) % 20), BOARD_Y + 50 * (static_cast<int>(y))}, PLAYER, 50, 50, FL_WHITE);
                line.push_back(cell);
            }
            else if (boardModel->getLogicCellVector()[y][x]->hasBox())
            {
                Cell *cell = new Cell(Point{BOARD_X + 50 * (static_cast<int>(x) % 20), BOARD_Y + 50 * (static_cast<int>(y))}, BOX, 50, 50, boardModel->getLogicCellVector()[y][x]->getBox()->color);
                line.push_back(cell);
            }
            else if (boardModel->getLogicCellVector()[y][x]->getType() == BOX_FINAL_POS)
            {
                Cell *cell = new Cell(Point{BOARD_X + 50 * (static_cast<int>(x) % 20), BOARD_Y + 50 * (static_cast<int>(y))}, BOX_FINAL_POS, 50, 50, boardModel->getLogicCellVector()[y][x]->getColor());
                line.push_back(cell);
            }
            else
            {
                Cell *cell = new Cell(Point{BOARD_X + 50 * (static_cast<int>(x) % 20), BOARD_Y + 50 * (static_cast<int>(y))}, boardModel->getLogicCellVector()[y][x]->getType(), 50, 50, FL_BLACK);
                line.push_back(cell);
            }
        }
        cells.push_back(line);
        line.clear();
    }
}

DisplayBoard::~DisplayBoard()
{
    for (auto i : cells)
        for (auto j : i)
            delete j;
}

#endif