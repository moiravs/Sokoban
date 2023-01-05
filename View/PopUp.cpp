#include "PopUp.hpp"

PopUp::PopUp() : Fl_Window(400, 400, 400, 400, "Help")
{
    Fl::add_timeout(1.0 / REFRESH_PER_SECOND, Time_CB, this);
    resizable(this);
    this->show();

    levels->add("Level 1");
    levels->add("Level 2");
    levels->add("Level 3");
    levels->add("Level 4");
    levels->show();
    levels->callback(windowCallback, this);
}
void PopUp::draw()
{
    Fl_Window::draw();
    fl_color(FL_BLACK);
    fl_draw("Choose Level", 100, 100);
}
void PopUp::Time_CB(void *userdata)
{
    Fl::repeat_timeout(1.0 / REFRESH_PER_SECOND, Time_CB, userdata);
}

void PopUp::windowCallback(Fl_Widget *widget, void *f)
{
    PopUp *a = static_cast<PopUp *>(f);
    a->hide();
}