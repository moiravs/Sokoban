#include "Cell.hpp"


class Board
{
private:
    std::vector<std::vector<Cell>> cells;
    
    int matrix_elements[3] = {0, 1, 2};
    Cell matrix_objects[3] = {Cell(matrix_elements[0]), Cell(matrix_elements[1]), Cell(matrix_elements[2])};
    void initialize();

public: 
    Board()
    {
        initialize();
    }
    bool solved();
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void keyPressed(int keyCode);
};                                        