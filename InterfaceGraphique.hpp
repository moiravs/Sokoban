#ifndef INTERFACEGRAPHIQUE_HPP
#define INTERFACEGRAPHIQUE_HPP
#include "Constants.hpp"
#include "Board.hpp"
#include "ControllerBoard.hpp"

struct Point
{
    int x, y;
};

class Rectangle
{
    Point center;
    int type;
    int w, h;
    Fl_Color fillColor, frameColor;
    Fl_JPEG_Image *personnage;
    Fl_PNG_Image *wall;

public:
    Rectangle(Point center, int type, int w, int h,
              Fl_Color frameColor = FL_BLACK,
              Fl_Color fillColor = FL_WHITE);
    void draw();
    void setFillColor(Fl_Color newFillColor);
    void setFrameColor(Fl_Color newFrameColor);
    bool contains(Point p);
};

class Cell
{
    Rectangle r;
    bool on = false;

public:
    Cell(Point center, int type, int w, int h);
    void draw();
    void mouseClick(Point mouseLoc);
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