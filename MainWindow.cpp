#include "MainWindow.hpp"
#include "Constantes.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <math.h>
#include <time.h>


class MainWindow : public Fl_Window
{
public:
    MainWindow() : Fl_Window(000, 000, windowWidth, windowHeight, "Lab 1")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
    }
    void draw() override
    {
        Fl_Window::draw();
        ::draw(); // Global draw function
    }
    int handle(int event) override
    {
        switch (event)
        {
        case FL_MOVE:
            mouseMove(Fl::event_x(), Fl::event_y());
            return 1;
        case FL_KEYDOWN:
            keyPressed(Fl::event_key());
        }
        return 0;
    }
    static void Timer_CB(void *userdata)
    {
        MainWindow *o = (MainWindow *)userdata;
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }
};
