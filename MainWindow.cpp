
#include "MainWindow.hpp"
class StartWindow : public Fl_Window
{
public:
    StartWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Lab 2")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
    }
    void draw() override
    {
        Fl_Window::draw();
    }
    static void Timer_CB(void *userdata)
    {
        StartWindow *o = static_cast<StartWindow *>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }
};

class MainWindow : public Fl_Window
{
    Board Board;

public:
    MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Lab 2")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
    }
    void draw() override
    {
        Fl_Window::draw();
        Board.draw();
    }
    int handle(int event) override
    {
        switch (event)
        {
        case FL_MOVE:
            Board.mouseMove(Point{Fl::event_x(), Fl::event_y()});
            return 1;
        case FL_PUSH:
            Board.mouseClick(Point{Fl::event_x(), Fl::event_y()});
            return 1;
        case FL_KEYDOWN:
            Board.keyPressed(Fl::event_key());
            return 1;
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
