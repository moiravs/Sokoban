

#include "Cell.hpp"

class Rectangle
{
    Point center;
    int w, h;
    Fl_Color fillColor, frameColor;

public:
    Rectangle(Point center, int w, int h,
              Fl_Color frameColor = FL_BLACK,
              Fl_Color fillColor = FL_WHITE);
    void draw();
    void setFillColor(Fl_Color newFillColor);
    Fl_Color getFillColor()
    {
        return fillColor;
    }
    void setFrameColor(Fl_Color newFrameColor);
    Fl_Color getFrameColor()
    {
        return frameColor;
    }
    void setWidth(int neww)
    {
        w = neww;
    }
    void setHeight(int newh)
    {
        h = newh;
    }
    int getWidth()
    {
        return w;
    }
    int getHeight()
    {
        return h;
    }
    bool contains(Point p);
    Point getCenter()
    {
        return center;
    }
};

Rectangle::Rectangle(Point center, int w, int h,
                     Fl_Color frameColor,
                     Fl_Color fillColor) : center{center}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor} {}

void Rectangle::draw()
{
    fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, fillColor);
    fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
}

void Rectangle::setFillColor(Fl_Color newFillColor)
{
    fillColor = newFillColor;
}

void Rectangle::setFrameColor(Fl_Color newFrameColor)
{
    frameColor = newFrameColor;
}

bool Rectangle::contains(Point p)
{
    return p.x >= center.x - w / 2 &&
           p.x < center.x + w / 2 &&
           p.y >= center.y - h / 2 &&
           p.y < center.y + h / 2;
}

/*--------------------------------------------------

Cell class.

The Canvas class below will have cells as instance
vraiables and call the methods of Cell
--------------------------------------------------*/

class Cell
{
    Rectangle r;
    bool bomb;
    bool visible = false;
    std::vector<Cell *> neighbors;
    Text textNeighborBombCount;

    // Private methods
    int neighborBombCount();
    void makeVisible(); // Used in the last step to reveal more than one cell

public:
    // Constructor
    Cell(Point center, int w, int h);

    // Methods that draw and handle events
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);

    // Used to initalize neighbors after all cells are created
    void setNeighbors(const vector<Cell *> newNeighbors)
    {
        neighbors = newNeighbors;
    }

    // Getters used by Canvas to see if the game is won/lost
    bool isBomb()
    {
        return bomb;
    }
    bool isVisible()
    {
        return visible;
    }

    // Use these instead of draw to see what you should have at the end of task 2/3
    void drawTaskTwo();
    void drawTaskThree();
};

Cell::Cell(Point center, int w, int h) : r(center, w, h, FL_BLACK, FL_WHITE),
                                         bomb{rand() % 8 == 0},
                                         textNeighborBombCount("", center, h / 2) {}

void Cell::draw()
{
    if (visible)
    {
        if (bomb)
        {
            r.setFillColor(FL_RED);
            r.draw();
        }
        else
        {
            r.setFillColor(FL_WHITE);
            r.draw();
            if (neighborBombCount() > 0)
            {
                textNeighborBombCount.setString(to_string(neighborBombCount()));
                textNeighborBombCount.draw();
            }
        }
    }
    else
    {
        r.setFillColor(fl_rgb_color(200, 150, 167));
        r.draw();
    }
}

// NOTE: Use this instead of draw to see how the game should function at the end of task 2
void Cell::drawTaskTwo()
{
    if (bomb)
    {
        r.setFillColor(FL_RED);
        r.draw();
    }
    else
    {
        r.setFillColor(FL_WHITE);
        r.draw();
    }
}

// NOTE: Use this instead of draw to see how the game should function at the end of task 3
void Cell::drawTaskThree()
{
    if (bomb)
    {
        r.setFillColor(FL_RED);
        r.draw();
    }
    else
    {
        r.setFillColor(FL_WHITE);
        r.draw();
        textNeighborBombCount.setString(to_string(neighborBombCount()));
        textNeighborBombCount.draw();
    }
}

void Cell::mouseMove(Point mouseLoc)
{
    if (r.contains(mouseLoc))
    {
        r.setFrameColor(FL_RED);
    }
    else
    {
        r.setFrameColor(FL_BLACK);
    }
}

void Cell::makeVisible()
{
    if (!visible)
    {
        visible = true;
        if (neighborBombCount() == 0)
            for (auto &neighbor : neighbors)
                neighbor->makeVisible();
    }
}

void Cell::mouseClick(Point mouseLoc)
{
    if (r.contains(mouseLoc))
    {
        makeVisible();
    }
}

int Cell::neighborBombCount()
{
    int bombCount = 0;
    for (auto &neighbor : neighbors)
        if (neighbor->isBomb())
            bombCount++;
    // #include<algorithm>
    // int bombCount = ranges::count_if(neighbors, [](auto &neighbor){return neighbor->isBomb();});
    return bombCount;
}
