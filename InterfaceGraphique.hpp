#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include <array>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include "Constants.hpp"

#include <FL/Fl_Menu_Bar.H>
#include <memory>
#include "Board.cpp"
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>

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

public:
    Rectangle(Point center, int type, int w, int h,
              Fl_Color frameColor = FL_BLACK,
              Fl_Color fillColor = FL_WHITE);
    void draw();
    void setFillColor(Fl_Color newFillColor);
    void setFrameColor(Fl_Color newFrameColor);
    bool contains(Point p);
};

Rectangle::Rectangle(Point center, int type, int w, int h,
                     Fl_Color frameColor,
                     Fl_Color fillColor) : center{center}, type{type}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor}
{
    this->personnage = new Fl_JPEG_Image("index.jpeg");
}

void Rectangle::draw()
{

    if (type == PLAYER)
    {
        Fl_Image *hihi = personnage;
        hihi->draw(center.x - w / 2, center.y - h / 2, w, h);
        // fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_BLUE);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, FL_BLUE);
    }
    else if (type == BOX)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_GREEN);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
    else if (type == EMPTY)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_RED);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
    else if (type == WALL)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_BLACK);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
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

class Cell
{
    Rectangle r;
    bool on = false;

public:
    Cell(Point center, int type, int w, int h);
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
};

Cell::Cell(Point center, int type, int w, int h) : r(center, type, w, h, FL_BLACK, FL_WHITE) {}
void Cell::draw()
{
    r.draw();
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
void Cell::mouseClick(Point mouseLoc)
{
    if (r.contains(mouseLoc))
    {
        on = !on;
        if (on)
            r.setFillColor(FL_YELLOW);
        else
            r.setFillColor(FL_WHITE);
    }
}

class DisplayBoard
{
private:
    std::shared_ptr<Board> boardmodel;
    std::vector<Cell> cells;

public:
    DisplayBoard(){};
    DisplayBoard(std::shared_ptr<Board> board)
    {
        // MainWindow MW = new MainWindow();
        // MW.show();
        this->boardmodel = board;
        for (size_t i = 0; i < boardmodel->getMatrix().size(); i++)
        {
            for (size_t j = 0; j < boardmodel->getMatrix()[0].size(); j++)
            {
                if (boardmodel->getMatrix()[i][j] == EMPTY)
                {
                    cells.push_back(Cell{Point{50 * ((int)i % 10) + 25, 50 * ((int)j) + 25}, 0, 50, 50});
                }
                else if (boardmodel->getMatrix()[i][j] == PLAYER)
                {
                    cells.push_back(Cell{Point{50 * ((int)i % 10) + 25, 50 * ((int)j) + 25}, 1, 50, 50});
                }
                else if (boardmodel->getMatrix()[i][j] == BOX)
                {
                    cells.push_back(Cell{Point{50 * ((int)i % 10) + 25, 50 * ((int)j) + 25}, 2, 50, 50});
                }
                else if (boardmodel->getMatrix()[i][j] == WALL)
                {
                    cells.push_back(Cell{Point{50 * ((int)i % 10) + 25, 50 * ((int)j) + 25}, 3, 50, 50});
                }
            }
        }
    };

    void printBoard()
    {
        for (size_t i = 0; i < boardmodel->getMatrix().size(); i++)
        {
            for (size_t j = 0; j < boardmodel->getMatrix()[0].size(); j++)
            {
                std::cout << boardmodel->getMatrix()[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
    void draw()
    {
        for (auto &c : cells)
            c.draw();
    }
};

class MainWindow : public Fl_Window
{
    DisplayBoard boardmodel;

public:
    MainWindow(DisplayBoard board) : Fl_Window(500, 500, windowWidth, windowHeight, "Lab 2")
    {
        this->boardmodel = board;
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);

        Fl_Menu_Bar *menu = new Fl_Menu_Bar(0, 0, 400, 25); // Create menubar, items..
        menu->add("&File/&Open", "^o", MyMenuCallback);
        menu->add("&File/&Save", "^s", MyMenuCallback, 0, FL_MENU_DIVIDER);
        menu->add("&File/&Quit", "^q", MyMenuCallback);
        menu->add("&Edit/&Copy", "^c", MyMenuCallback);
        menu->add("&Edit/&Paste", "^v", MyMenuCallback, 0, FL_MENU_DIVIDER);
        menu->add("&Edit/Radio 1", 0, MyMenuCallback, 0, FL_MENU_RADIO);
        menu->add("&Edit/Radio 2", 0, MyMenuCallback, 0, FL_MENU_RADIO | FL_MENU_DIVIDER);
        menu->add("&Edit/Toggle 1", 0, MyMenuCallback, 0, FL_MENU_TOGGLE);                 // Default: off
        menu->add("&Edit/Toggle 2", 0, MyMenuCallback, 0, FL_MENU_TOGGLE);                 // Default: off
        menu->add("&Edit/Toggle 3", 0, MyMenuCallback, 0, FL_MENU_TOGGLE | FL_MENU_VALUE); // Default: on
    }
    static void MyMenuCallback(Fl_Widget *w, void *)
    {
        Fl_Menu_Bar *bar = (Fl_Menu_Bar *)w;      // Get the menubar widget
        const Fl_Menu_Item *item = bar->mvalue(); // Get the menu item that was picked

        char ipath[256];
        bar->item_pathname(ipath, sizeof(ipath)); // Get full pathname of picked item

        fprintf(stderr, "callback: You picked '%s'", item->label()); // Print item picked
        fprintf(stderr, ", item_pathname() is '%s'", ipath);         // ..and full pathname

        if (item->flags & (FL_MENU_RADIO | FL_MENU_TOGGLE))
        {                                                                   // Toggle or radio item?
            fprintf(stderr, ", value is %s", item->value() ? "on" : "off"); // Print item's value
        }
        fprintf(stderr, "\n");
        if (strcmp(item->label(), "&Quit") == 0)
        {
            exit(0);
        }
    }
    void draw() override
    {
        Fl_Window::draw();
        this->boardmodel.draw();
    }
    /*
    int handle(int event) override
    {

        switch (event)
        {
        case FL_MOVE:
            canvas.mouseMove(Point{Fl::event_x(), Fl::event_y()});
            return 1;
        case FL_PUSH:
            canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
            return 1;
        case FL_KEYDOWN:
            canvas.keyPressed(Fl::event_key());
            return 1;
        }
        return 0;
    }*/
    static void Timer_CB(void *userdata)
    {
        MainWindow *o = static_cast<MainWindow *>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }
};
