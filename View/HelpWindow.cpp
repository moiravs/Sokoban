#include "HelpWindow.hpp"

HelpWindow::HelpWindow() : Fl_Window(400, 400, 400, 400, "Help")
{
    Fl::add_timeout(1.0 / refreshPerSecond, Time_CB, this);
    resizable(this);
    this->show();
    this->callback(windowCallback, this);
}
void HelpWindow::draw() 
{
    Fl_Window::draw();
    fl_color(FL_BLACK);
    fl_draw("To Teleport Yourself, press A ", 100, 100);
}
void HelpWindow::Time_CB(void *userdata)
{
    Fl::repeat_timeout(1.0 / refreshPerSecond, Time_CB, userdata);
}

void HelpWindow::windowCallback(Fl_Widget *widget, void *f)
{
    HelpWindow *a = ((HelpWindow *)f);
    a->hide();
}