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
    std::shared_ptr<Board> boardmodel;
    std::vector<Cell> cells;

public:
    DisplayBoard(std::shared_ptr<Board> board) ;

    DisplayBoard() : Fl_Box(boardx, boardy, boardw, boardh){};
    void printBoard();

    void update();

    void draw();
};

class MainWindow : public Fl_Window
{

    std::shared_ptr<Board> boardi;
    ControllerBoard *control;
    DisplayBoard *display;
    Fl_Button *reset;
    Fl_Choice *levels;
    const char *pas;
    Fl_Text_Buffer *buff;

        public : MainWindow(std::shared_ptr<Board> boardi);

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
        if (Fl::event_inside(this->display)) // if event inside board
        {
            if (event == FL_PUSH)
            {
                //control->board_handle(event);
                return 1;
            }
        }
        if (Fl::event_inside(this->reset)) // if event inside board
        {
            if (event == FL_PUSH)
            {
                control->reset_handle();
                display->update();
            }
        }
        if (Fl::event_inside(this->levels)) // if event inside board
        {
            if (event == FL_PUSH)
            {
                int i = this->levels->value();
                control->level_change(i);
                display->update();
            }
        }

        if (event == FL_KEYBOARD)
        {
            puts("ahh1");
            control->board_handle(event);
            puts("ahh2");
            std::string pas = "pas " + std::to_string(control->pas);
            puts("ahh3");
            const char *paschar = pas.c_str();
            this->buff->text(paschar);
            puts("ahh");
            display->update();
        }
        return Fl_Window::handle(event);

    }
    static void Timer_CB(void *userdata)
    {
        MainWindow *o = static_cast<MainWindow *>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }
};
#endif