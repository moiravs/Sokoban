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
    fl_color(FL_BLACK);
    fl_font(Fl_Font(1),20);
    fl_draw("Andrius Ezerskis & Moïra Vanderslagmolen", 200, 400);
    fl_font(Fl_Font(1), 24);
    fl_draw("Projet de Language de Programmation - Sokoban", 200, 300);
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