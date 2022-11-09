#include "Cell.hpp"


class Board
{
private:
    std::vector<std::vector<Cell>> cells;
    
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
    void clear();
};                                        