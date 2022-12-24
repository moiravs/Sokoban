#include "StartWindow.hpp"

StartWindow::StartWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "SOKOBAN")
{
    Fl::add_timeout(1.0 / refreshPerSecond, Time_CB, this);
    resizable(this);
    this->show();
}
void StartWindow::draw()
{
    Fl_Window::draw();
    fl_draw("SOKOBAN", 300, 300);
}
void StartWindow::Time_CB(void *userdata)
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