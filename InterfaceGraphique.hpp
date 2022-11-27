#ifndef INTERFACEGRAPHIQUE_HPP
#define INTERFACEGRAPHIQUE_HPP
#include "Constants.hpp"
#include "Board.hpp"
#include "ControllerBoard.hpp"

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

class MainWindow : public Fl_Window
{

    std::shared_ptr<BoardModel> boardModel;
    ControllerBoard *control;
    DisplayBoard *display;
    Fl_Button *reset;
    Fl_Choice *levels;
    const char *pas;
    Fl_Text_Buffer *buff;

public:
    MainWindow(std::shared_ptr<BoardModel> boardModel);

    static void MyMenuCallback(Fl_Widget *w, void *);
    void draw() override;

    int handle(int event) override;

    static void Timer_CB(void *userdata);
};
#endif