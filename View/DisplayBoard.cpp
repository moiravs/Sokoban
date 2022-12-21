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

    std::string pas = "pas " + std::to_string(this->boardmodel->pas);
    fl_draw(pas.c_str(), pasx, pasy);
    std::string limitpas = "limite de pas " + std::to_string(this->boardmodel->limitpas);
    fl_draw(limitpas.c_str(), limitpasx, limitpasy);
    std::string minpas = "min pas for this level" + std::to_string(this->boardmodel->minpas);
    fl_draw(minpas.c_str(), limitpasx + 20, limitpasy + 80);
}

DisplayBoard::DisplayBoard(std::shared_ptr<BoardModel> board) : Fl_Box(boardx, boardy, boardw, boardh) 
{
    this->boardmodel = board;
    this->update();
}

std::tuple<int, int> DisplayBoard::mouseClick(Point mouseLoc)
{
    for (size_t i = 0; i < 63; i++)
    {
        if (cells[i].mouseClick(mouseLoc))
            return std::tuple<int, int>(i / 8, i % 8);
    }    
}

void DisplayBoard::update()
{
    cells.clear();
    for (size_t y = 0; y < boardmodel->LogicCellVector.size(); y++)
    {
        for (size_t x = 0; x < boardmodel->LogicCellVector[y].size(); x++)
        {
            if (boardmodel->LogicCellVector[y][x]->hasPlayer())
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, PLAYER, 50, 50, FL_BLACK});
            else if (boardmodel->LogicCellVector[y][x]->hasBox())
            {
                if (boardmodel->LogicCellVector[y][x]->getBox()->getLight() == false)
                    cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, BOX, 50, 50, boardmodel->LogicCellVector[y][x]->getBox()->getColor()});
                else if (boardmodel->LogicCellVector[y][x]->getBox()->getLight() == true)
                    cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, LIGHT_BOX, 50, 50, FL_DARK_BLUE});
            }
            else if (boardmodel->LogicCellVector[y][x]->getType() == WALL)
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, WALL, 50, 50, FL_DARK_YELLOW});
            else if (boardmodel->LogicCellVector[y][x]->getType() == BOX_FINAL_POS)
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, BOX_FINAL_POS, 50, 50, boardmodel->LogicCellVector[y][x]->getColor()});
            else if (boardmodel->LogicCellVector[y][x]->getType() == EMPTY)
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, EMPTY, 50, 50, FL_BLACK});
            else if (boardmodel->LogicCellVector[y][x]->getType() == TELEPORTATION)
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, TELEPORTATION, 50, 50, FL_DARK_GREEN});
            else
                std::cout << boardmodel->LogicCellVector[y][x]->getType() << std::endl;
        }
    }
}

#endif