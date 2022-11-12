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

class MainWindow : public Fl_Window
{

public:
    MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Lab 2")
    {
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
        //board.draw();
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

class DisplayBoard
{
private:
    std::shared_ptr<Board> boardmodel;

public:
    DisplayBoard(std::shared_ptr<Board> board)
    {
        // MainWindow MW = new MainWindow();
        // MW.show();
        this->boardmodel = board;
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
};
