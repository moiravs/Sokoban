/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "MainWindow.hpp"

MainWindow::MainWindow(std::shared_ptr<BoardModel> boardModel, PopUp *popUp) : Fl_Window(500, 500, windowWidth, windowHeight, "Lab 2")
{
    resizable(this);
    this->boardModel = boardModel;
    DisplayBoard *board = new DisplayBoard(boardModel);
    display = board;
    board->show();
    this->popUp = popUp;
    Fl_Button *reset = new Fl_Button(resetx, resety, resetw, reseth, "reset level");
    Fl_Button *resetminpas = new Fl_Button(resetminpasx, resetminpasy, resetminpasw, resetminpash, "reset min steps");
    Fl_Choice *levels = new Fl_Choice(choicex, choicey, choicew, choiceh, "levels");
    levels->add("Level 1");
    levels->add("Level 2");
    levels->add("Level 3");
    this->callback(this->windowCallback, this);
    reset->callback(resetLevelCallback, (void *)this);
    levels->callback(changeLevelCallback, (void *)this);
    resetminpas->callback(resetMinStepsCallback, (void *)this);
    this->resizable(levels);
    this->resizable(resetminpas);
    this->resizable(reset);
    Fl_Menu_Bar *menu = new Fl_Menu_Bar(0, 0, 400, 25); // Create menubar, items..
    menu->add("&Game/&ChooseLevel", "^l", MyMenuCallback, this);
    menu->add("&Game/&Help", "^o", MyMenuCallback, this);
    menu->add("&File/&Save", "^s", MyMenuCallback, this, FL_MENU_DIVIDER);
    menu->add("&File/&Quit", "^q", MyMenuCallback, this);
}

void MainWindow::MyMenuCallback(Fl_Widget *w, void *userdata)
{
    MainWindow *o = static_cast<MainWindow *>(userdata);

    Fl_Menu_Bar *bar = (Fl_Menu_Bar *)w;      // Get the menubar widget
    const Fl_Menu_Item *item = bar->mvalue(); // Get the menu item that was picked
    if (strcmp(item->label(), "&ChooseLevel") == 0)
    {
        o->popUp->set_modal();
        o->popUp->show();
        while (o->popUp->shown())
            Fl::wait();
        o->changeLevelCallback(o->popUp->levels, (void *)o);
    }
    if (item->flags & (FL_MENU_RADIO | FL_MENU_TOGGLE))
        fprintf(stderr, ", value is %s", item->value() ? "on" : "off"); // Print item's value
    fprintf(stderr, "\n");
    if (strcmp(item->label(), "&Quit") == 0)
        exit(0);
}

void MainWindow::draw()
{
    Fl_Window::draw();
    if (this->boardModel->endOfParty == true)
    {
        if (this->boardModel->winorlose == true)
        {
            std::string wonstring = "YOU WON with " + std::to_string(boardModel->stepsLimit - boardModel->steps) + " steps restants, reset or change level";
            fl_draw(wonstring.c_str(), limitpasx + 50, limitpasy + 50);
        }
        else
        {
            fl_draw("YOU LOSE, reset or change level", limitpasx + 50, limitpasy + 50);
        }
    }
    fl_font(Fl_Font(1), 16);
    std::string steps = "Steps : " + std::to_string(this->boardModel->steps);
    fl_draw(steps.c_str(), pasx, pasy);
    std::string stepsLimit = "Steps limit : " + std::to_string(this->boardModel->stepsLimit);
    fl_draw(stepsLimit.c_str(), limitpasx, limitpasy);
    std::string minimumSteps = "Minimum Steps : " + std::to_string(this->boardModel->minimumSteps);
    fl_draw(minimumSteps.c_str(), minpasx, minpasy);
}

int MainWindow::handle(int event)
{

    if (boardModel->endOfParty == false)
    {

        if (event == FL_KEYBOARD)
        {
            if (Fl::event_key() == FL_Up)
            {
                boardModel->move(boardModel->player->y - 1, boardModel->player->x);
            }
            else if (Fl::event_key() == FL_Down)
            {
                boardModel->move(boardModel->player->y + 1, boardModel->player->x);
            }
            else if (Fl::event_key() == FL_Right)
            {
                boardModel->move(boardModel->player->y, boardModel->player->x + 1);
            }
            else if (Fl::event_key() == FL_Left)
            {
                boardModel->move(boardModel->player->y, boardModel->player->x - 1);
            }
            else if (Fl::event_key(97))
            {
                boardModel->teleport();
            }

            if ((this->boardModel->steps == this->boardModel->stepsLimit) || (this->boardModel->isFailure()))
            {
                this->boardModel->endOfParty = true;
                this->boardModel->winorlose = false;
            }

            if (this->boardModel->isEndOfParty())
            {
                this->boardModel->endOfParty = true;
                this->boardModel->winorlose = true;
            }
            display->update();
            this->redraw();
        }

        if (Fl::event_inside(this->display))
        {
            if (event == FL_PUSH)
            {
                std::tuple<int, int> position = display->mouseClick(Point{Fl::event_x(), Fl::event_y()});
                this->boardModel->moveTo(std::get<1>(position), std::get<0>(position));
                display->update();
                this->redraw();
            }
        }
    }

    if (Fl::event_inside(this)) // if
    {
        if (event == FL_PUSH)
        {
            display->update();
            this->redraw();
        }
    }

    return Fl_Window::handle(event);
}

void MainWindow::Timer_CB(void *userdata)
{
    MainWindow *o = static_cast<MainWindow *>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
}


void MainWindow::windowCallback(Fl_Widget *widget, void *f)
{
    MainWindow *a = ((MainWindow *)f);
    widget->hide();
    a->saveMinimumSteps();
}

void MainWindow::resetLevelCallback(Fl_Widget *w, void *f)
{
    
    MainWindow *a = ((MainWindow *)f);
    a->boardModel->steps = 0;
    a->boardModel->endOfParty = false;
    a->boardModel->createBoard(a->boardModel->readFileIntoString());
    a->display->update();
    a->redraw();
}

void MainWindow::saveMinimumSteps()
{
    if (((this->boardModel->steps < this->boardModel->minimumSteps) && (this->boardModel->winorlose == true)) || ((this->boardModel->minimumSteps == 0) && (this->boardModel->winorlose == true)))
    {
        std::string strReplace = "l" + std::to_string(this->boardModel->minimumSteps);
        std::string strNew = "l" + std::to_string(this->boardModel->steps);
        std::ifstream filein(this->boardModel->filename); // File to read from
        std::ofstream fileout("fileout.txt");             // Temporary file
        if (!filein || !fileout)
        {
            std::cout << "Error opening files!" << std::endl;
        }

        std::string strTemp;
        bool found = false;
        while (filein >> strTemp)
        {
            if ((strTemp == strReplace) && (found == false))
            {
                strTemp = strNew;
                found = true;
            }
            strTemp += "\n";
            fileout << strTemp;
        }
        filein.close();
        std::remove(this->boardModel->filename.c_str());
        std::rename("fileout.txt", this->boardModel->filename.c_str());
    }
    this->redraw();
}

void MainWindow::changeLevelCallback(Fl_Widget *widget, void *f)
{
    MainWindow *mainWindow = ((MainWindow *)f);
    puts("brurirjoekh");
    Fl_Choice *levels = (Fl_Choice *)widget;
    int choice = levels->value();
    mainWindow->saveMinimumSteps();
    mainWindow->boardModel->endOfParty = false;
    switch (choice)
    {
    case -1:
        return;
    case 0:
        mainWindow->boardModel->filename = level1;
        break;
    case 1:
        mainWindow->boardModel->filename = level2;
        break;
    case 2:
        mainWindow->boardModel->filename = level3;
        break;
    }
    mainWindow->boardModel->createBoard(mainWindow->boardModel->readFileIntoString());
    mainWindow->display->update();
    mainWindow->redraw();
}

void MainWindow::resetMinStepsCallback(Fl_Widget *w, void *f)
{
    MainWindow *mainWindow = ((MainWindow *)f);
    mainWindow->boardModel->minimumSteps = 0;
    mainWindow->redraw();
}
