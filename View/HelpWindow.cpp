/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "HelpWindow.hpp"

HelpWindow::HelpWindow() : Fl_Window(400, 400, 400, 400, "Help") // Source : Programmation Language Course
{
    Fl::add_timeout(1.0 / REFRESH_PER_SECOND, Time_CB, this);
    resizable(this);
    this->show();
    this->callback(windowCallback, this);
    levels->add("Level 1");
    levels->add("Level 2");
    levels->add("Level 3");
    levels->add("Level 4");
    levels->hide();
    levels->callback(windowCallback, this);
}
void HelpWindow::draw()
{
    Fl_Window::draw();
    if (help == true)
    {
        levels->hide();
        fl_color(FL_BLACK);
        fl_draw("To Teleport Yourself, press A ", 100, 100);
        fl_draw("To go on the left, press Left Arrow", 100, 130);
        fl_draw("To go on the right, press Right Arrow", 100, 160);
        fl_draw("To go up, press Up Arrow ", 100, 190);
        fl_draw("To go down, press Down Arrow", 100, 220);
    }
    else {
        levels->show();
    }
}
void HelpWindow::Time_CB(void *userdata) // Source : Programmation Language Course
{
    Fl::repeat_timeout(1.0 / REFRESH_PER_SECOND, Time_CB, userdata);
}

void HelpWindow::windowCallback(Fl_Widget *widget, void *f)
{
    HelpWindow *a = static_cast<HelpWindow *>(f);
    a->hide();
}