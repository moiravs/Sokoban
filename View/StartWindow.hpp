#include "../View/DisplayBoard.hpp"
#include "../View/CellDisplay.hpp"

class StartWindow : public Fl_Window
{
private:
    Fl_Button *button = new Fl_Button(300, 300, 400, 50, "Andrius Ezerskis & Moïra Vanderslagmolen");
    int wait = 0;

public:
    StartWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "SOKOBAN")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Time_CB, this);
        resizable(this);
        this->show();
    }
    void draw() override
    {
        Fl_Window::draw();
        fl_draw("SOKOBAN", 300, 300);
    }
    static void Time_CB(void *userdata)
    {
        StartWindow *o = static_cast<StartWindow *>(userdata);
        o->wait++;
        if (o->wait == 10)
        {
            sleep(1);
            o->hide();
        }
        Fl::repeat_timeout(1.0 / refreshPerSecond, Time_CB, userdata);
    }
};