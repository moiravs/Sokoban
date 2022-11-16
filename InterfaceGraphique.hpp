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
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
};

class DisplayBoard : public Fl_Box
{
private:
    std::shared_ptr<Board> boardmodel;
    std::vector<Cell> cells;

public:
    DisplayBoard() : Fl_Box(0, 0, 500, 500){};
    void printBoard();

    DisplayBoard(std::shared_ptr<Board> board) : Fl_Box(0, 0, 500, 500)
    {
        this->boardmodel = board;
        for (size_t i = 0; i < boardmodel->getBoard().size(); i++)
        {
            for (size_t j = 0; j < boardmodel->getBoard()[0].size(); j++)
            {
                if (boardmodel->getBoard()[i][j] == EMPTY)
                {
                    cells.push_back(Cell{Point{50 * ((int)i % 10) + 25, 50 * ((int)j) + 25}, 0, 50, 50});
                }
                else if (boardmodel->getBoard()[i][j] == PLAYER)
                {
                    cells.push_back(Cell{Point{50 * ((int)i % 10) + 25, 50 * ((int)j) + 25}, 1, 50, 50});
                }
                else if (boardmodel->getBoard()[i][j] == BOX)
                {
                    cells.push_back(Cell{Point{50 * ((int)i % 10) + 25, 50 * ((int)j) + 25}, 2, 50, 50});
                }
                else if (boardmodel->getBoard()[i][j] == WALL)
                {
                    cells.push_back(Cell{Point{50 * ((int)i % 10) + 25, 50 * ((int)j) + 25}, 3, 50, 50});
                }
            }
        }
    };

    void draw();
};

class MainWindow : public Fl_Window
{

    std::shared_ptr<Board> boardi;
    ControllerBoard *ahhe;

public:
    MainWindow(std::shared_ptr<Board> boardi) : Fl_Window(500, 500, windowWidth, windowHeight, "Lab 2")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
        this->boardi = boardi;
        DisplayBoard *board = new DisplayBoard(boardi);
        board->show();
        ControllerBoard * boarda = new ControllerBoard(boardi);
        ahhe = boarda;

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
    }
    
    int handle(int event) override
    {
        if (event == FL_PUSH){
        ahhe->key_handle(event);
        return 1;
        }
        else if (event == FL_KEYBOARD){
            if (Fl::event_key() ==  FL_Up){
                ahhe->key_handle(event);
            }
        }
        return 0;
        
    }
    static void Timer_CB(void *userdata)
    {
        MainWindow *o = static_cast<MainWindow *>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }
};
#endif