
#include "MainWindow.hpp"



class StartWindow : public Fl_Window
{
private:
    Fl_Button *button = new Fl_Button(200, 200, 100, 50, "Start the game");

public:
    StartWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Start the game")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
        this->show();

        button->tooltip("Make advanced search");
        button->callback((Fl_Callback *)ad_cb);
    }
    void draw() override
    {
        Fl_Window::draw();
        Fl_Widget *b = button;
        b->draw();
    }
    static void Timer_CB(void *userdata)
    {
        StartWindow *o = static_cast<StartWindow *>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }

    static void ad_cb(Fl_Button *theButton, void *)
    {
    }
};
