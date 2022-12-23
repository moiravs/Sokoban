#include "DisplayBoard.hpp"
#include "CellDisplay.hpp"

class HelpWindow : public Fl_Window
{
private:
public:
    HelpWindow() : Fl_Window(400, 400, 400, 400, "Help")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Time_CB, this);
        resizable(this);
        this->show();
        this->callback(windowCallback, this);
    }
    void draw() override
    {
        Fl_Window::draw();
        fl_color(FL_BLACK);
        fl_draw("To Teleport Yourself, press A ", 100, 100);
    }
    static void Time_CB(void *userdata)
    {
        Fl::repeat_timeout(1.0 / refreshPerSecond, Time_CB, userdata);
    }
    void window_non_static_cb(Fl_Widget *widget)
    {
        this->hide();
    }

    static void windowCallback(Fl_Widget *widget, void *f)
    {
        ((HelpWindow *)f)->window_non_static_cb(widget);
    }
};