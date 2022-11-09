#include "Cell.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class BoardModel
{
private:
    std::vector<std::vector<CellModel>> cells;
    void initialize();
public: 
    BoardModel()
    {
        initialize();
    }
    bool solved();
    std::vector<std::vector<CellModel>> getCells();
};                                        


class BoardController
{
private:
    BoardModel boardModel;
    BoardView boardView;
public:
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void keyPressed(int keyCode);
    void getBoard(std::string fileName);
};

class BoardView{
private:

public:
    void draw();
    void clear();
};