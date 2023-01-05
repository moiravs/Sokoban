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
    std::shared_ptr<BoardModel> boardModel;
    std::vector<Cell> cells;

public:
    //Constructors
    DisplayBoard() : Fl_Box(boardx, boardy, boardw, boardh){};
    DisplayBoard(std::shared_ptr<BoardModel> boardModel) : Fl_Box(boardx, boardy, boardw, boardh), boardModel{boardModel} { this->update(); }

    //Methods
    /**
     * @brief  Iterates over a vector of cell, and if the mouse location is in the cell, 
     * returns a tuple with the position of the cell
     * @param  mouseLoc: the Location of the mouse
     * @retval The position of the cell where the mouse location is
     */
    std::tuple<int, int> mouseClick(Point mouseLoc);
    /**
     * @brief  Updates the CellDisplayVector
     * @retval None
     */
    void update();
    /**
     * @brief  Draws the board
     * @retval None
     */
    void draw();
};
#endif