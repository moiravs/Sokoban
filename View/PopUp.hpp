#include "DisplayBoard.hpp"
#include "CellDisplay.hpp"

class PopUp : public Fl_Window
{
private:
public:
    Fl_Choice *levels = new Fl_Choice(100, 150, 200, 50);

    PopUp() : Fl_Window(400, 400, 400, 400, "Levels")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Time_CB, this);
        resizable(this);
        this->show();

        levels->add("Level 1");
        levels->add("Level 2");
        levels->add("Level 3");
        levels->show();
        levels->callback(windowCallback, this);
    }
    void draw() override
    {
        Fl_Window::draw();
        fl_color(FL_BLACK);
        fl_draw("Choose Level", 100, 100);
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
        ((PopUp *)f)->window_non_static_cb(widget);
    }
};