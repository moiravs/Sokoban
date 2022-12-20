#ifndef INTERFACEGRAPHIQUE_HPP
#define INTERFACEGRAPHIQUE_HPP
#include "../Constants.hpp"
#include "../Controller/ControllerBoard.hpp"
#include "../Model/BoardModel.hpp"

struct Point
{
    int x, y;
};

class Sketchable
{
public:
    virtual void draw() = 0;
    virtual bool contains(Point p) const = 0;
    virtual Point getCenter() const = 0;
    virtual ~Sketchable() {}
};
struct Translation
{
    explicit Translation(Point p)
    {
        fl_push_matrix();
        fl_translate(p.x, p.y);
    }
    ~Translation() { fl_pop_matrix(); }
};


class BoxDisplay
{
    Point center;
    int w, h;
    Fl_PNG_Image *wall;

public:
    BoxDisplay(Point center, int w, int h);
    void draw();
};

class PlayerDisplay
{
    Point center;
    int w, h;
    Fl_JPEG_Image *personnage;

public:
    PlayerDisplay(Point center, int w, int h);
    void draw();
};

class Cell : public Sketchable
{
    bool on = false;
    Point center;
    int type;
    int w, h;
    Fl_Color fillColor, frameColor;
    PlayerDisplay *personnage;
    Fl_PNG_Image *wall;
    BoxDisplay *box;
    int color;

public:
    Cell(Point center, int type, int w, int h, int color);
    void draw();
    bool contains(Point p) const override;
    Point getCenter() const override { return center; }
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