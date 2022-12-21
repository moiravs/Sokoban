/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef INTERFACEGRAPHIQUE_HPP
#define INTERFACEGRAPHIQUE_HPP
#include "../Constants.hpp"
#include "../Model/BoardModel.hpp"
#include "CellDisplay.hpp"

class DisplayBoard : public Fl_Box
{
private:
    std::shared_ptr<BoardModel> boardmodel;
    std::vector<Cell> cells;

public:
    DisplayBoard(std::shared_ptr<BoardModel> board);
    DisplayBoard() : Fl_Box(boardx, boardy, boardw, boardh){};
    std::tuple<int, int> mouseClick(Point mouseLoc);
    void update();
    void draw();
};
#endif