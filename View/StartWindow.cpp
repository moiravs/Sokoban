/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "StartWindow.hpp"

StartWindow::StartWindow() : Fl_Window(500, 500, WINDOW_WIDTH, WINDOW_HEIGHT, "SOKOBAN") // Source : Programmation Language Course
{
    Fl::add_timeout(1.0 / REFRESH_PER_SECOND, Time_CB, this);
    resizable(this);
    this->show();
}
void StartWindow::draw()
{
    Fl_Window::draw();
    fl_draw("SOKOBAN", 300, 300);
}
void StartWindow::Time_CB(void *userdata) // Source : Programmation Language Course
{
    StartWindow *o = static_cast<StartWindow *>(userdata);
    o->wait++;
    if (o->wait == 10)
    {
        sleep(1);
        o->hide();
    }
    Fl::repeat_timeout(1.0 / REFRESH_PER_SECOND, Time_CB, userdata);
}