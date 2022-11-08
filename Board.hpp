#include <map>
#include <iostream>
#include "Constantes.hpp"
#include "Cell.hpp"
#include "Wall.hpp"

class Board
{
private:
    Text textGameOver{"Game Over", {250, 250}, 90, fl_rgb_color(255, 0, 255)};
    Text textYouWin{"You Win!", {250, 250}, 90, FL_GREEN};
    vector<vector<Cell>> cells;
    vector<Cell> neighbors(int x, int y);
    int neighborBombCount(int x, int y);
    void initialize();
    int matrix_elements[3] = {0, 1, 2};
    Cellmatrix_objects = {new Cell(matrix_elements[0]), new Cell(matrix_elements[1]), new Cell(matrix_elements[2])}

    public : Board()
    {
        initialize();
    }
    bool bombExposed();
    bool solved();
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void keyPressed(int keyCode);
};