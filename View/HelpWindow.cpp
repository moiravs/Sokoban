/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "HelpWindow.hpp"

HelpWindow::HelpWindow() : Fl_Window(HELP_W_X, HELP_W_Y, HELP_W_W, HELP_W_H, "Help") // Source : Programmation Language Course
{
    Fl::add_timeout(1.0 / REFRESH_PER_SECOND, Time_CB, this);
    resizable(this);
    this->show();
    this->callback(windowCallback, this);
    level1->hide();
    level2->hide();
    level3->hide();
    level4->hide();
    level1->callback(windowCallback, this);
    level2->callback(windowCallback, this);
    level3->callback(windowCallback, this);
    level4->callback(windowCallback, this);
}
void HelpWindow::draw()
{
    Fl_Window::draw();
    if (help == true)
    {
        level1->hide();
        level2->hide();
        level3->hide();
        level4->hide();
        fl_color(FL_BLACK);
        fl_draw("To Teleport Yourself, press A ", 100, 100);
        fl_draw("To go on the left, press Left Arrow", 100, 130);
        fl_draw("To go on the right, press Right Arrow", 100, 160);
        fl_draw("To go up, press Up Arrow ", 100, 190);
        fl_draw("To go down, press Down Arrow", 100, 220);
    }
    else
    {
        level1->show();
        level2->show();
        level3->show();
        level4->show();
    }
}
void HelpWindow::Time_CB(void *userdata) // Source : Programmation Language Course
{
    Fl::repeat_timeout(1.0 / REFRESH_PER_SECOND, Time_CB, userdata);
}

void HelpWindow::windowCallback(Fl_Widget *widget, void *f)
{
    HelpWindow *a = static_cast<HelpWindow *>(f);
    std::cout << widget->label();
    if (strcmp(widget->label(),"Level1")==0)
        a->levelsValue = 0;
    if (strcmp(widget->label(), "Level2") == 0)
        a->levelsValue = 1;
    if (strcmp(widget->label(), "Level3") == 0)
        a->levelsValue = 2;
    if (strcmp(widget->label(), "Level4") == 0)
        a->levelsValue = 3;
    a->hide();
}