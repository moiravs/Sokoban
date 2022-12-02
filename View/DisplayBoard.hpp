#ifndef INTERFACEGRAPHIQUE_HPP
#define INTERFACEGRAPHIQUE_HPP
#include "../Constants.hpp"
#include "../Controller/ControllerBoard.hpp"
#include "../Model/BoardModel.hpp"

struct Point
{
    int x, y;
};
/*
class Box
{
    Point center;
    int w, h;
    Fl_JPEG_Image *wall;

public:
    Box();
    void draw();
};
class Player
{
    Point center;
    int w, h;
    Fl_JPEG_Image *personnage;

public:
    Player();
    void
    draw();
};*/

class Cell
{
    bool on = false;
    Point center;
    int type;
    int w, h;
    Fl_Color fillColor, frameColor;
    Fl_JPEG_Image *personnage;
    Fl_PNG_Image *wall;

public:
    Cell(Point center, int type, int w, int h);
    void draw();
    bool mouseClick(Point mouseLoc);
};

class DisplayBoard : public Fl_Box
{
private:
    std::shared_ptr<BoardModel> boardmodel;
    std::vector<Cell> cells;

public:
    DisplayBoard(std::shared_ptr<BoardModel> board);

    DisplayBoard() : Fl_Box(boardx, boardy, boardw, boardh){};
    void printBoard();
    void mouseClick(Point mouseLoc);
    void update();

    void draw();
};


#endif