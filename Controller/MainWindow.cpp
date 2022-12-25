/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */

#include "MainWindow.hpp"

MainWindow::MainWindow(std::shared_ptr<BoardModel> boardModel, PopUp *popUp, HelpWindow *helpWindow) : Fl_Window(500, 500, windowWidth, windowHeight, "Sokoban")
{
    resizable(this);
    this->boardModel = boardModel;
    this->helpWindow = helpWindow;
    DisplayBoard *board = new DisplayBoard(boardModel);
    display = board;
    board->show();
    this->popUp = popUp;
    // Initialisation of the buttons
    Fl_Button *reset = new Fl_Button(resetx, resety, resetw, reseth, "Reset Level");
    Fl_Button *resetMinSteps = new Fl_Button(resetminpasx, resetminpasy, resetminpasw, resetminpash, "Reset Min Steps");
    Fl_Button *levels = new Fl_Button(choicex, choicey, choicew, choiceh, "Levels");
    Fl_Button *help = new Fl_Button(helpx, helpy, helpw, helph, "Help");
    // Callback for the buttons
    help->callback(helpCallback, (void *)this);
    this->callback(this->windowCallback, this);
    reset->callback(resetLevelCallback, (void *)this);
    levels->callback(changeLevelCallback, (void *)this);
    resetMinSteps->callback(resetMinStepsCallback, (void *)this);

    this->resizable(levels);
    this->resizable(resetMinSteps);
    this->resizable(reset);
    this->resizable(help);
}

void MainWindow::draw()
{
    Fl_Window::draw();

    if (this->boardModel->isEndOfParty())
    {
        if (this->boardModel->getWinOrLose())
        {
            std::string wonstring = "You won with " + std::to_string(boardModel->getStepsLimit() - boardModel->getSteps()) + " steps left, reset or change level";
            fl_draw(wonstring.c_str(), winorlosex, winorlosey);
            this->boardModel->saveMinimumSteps();
        }
        else
        {
            fl_draw("You lose, reset or change level", winorlosex, winorlosey);
        }
    }
    fl_font(Fl_Font(1), 16);
    std::string steps = "Steps : " + std::to_string(this->boardModel->getSteps());
    fl_draw(steps.c_str(), pasx, pasy);
    std::string stepsLimit = "Steps limit : " + std::to_string(this->boardModel->getStepsLimit());
    fl_draw(stepsLimit.c_str(), limitpasx, limitpasy);
    std::string minimumSteps = "Minimum Steps : " + std::to_string(this->boardModel->getMinimumSteps());
    fl_draw(minimumSteps.c_str(), minpasx, minpasy);
}

int MainWindow::handle(int event)
{

    if (event == FL_KEYBOARD && boardModel->isEndOfParty() == false)
    {
        if (Fl::event_key() == FL_Up)
            boardModel->move(boardModel->getPlayer()->y - 1, boardModel->getPlayer()->x);
        else if (Fl::event_key() == FL_Down)
            boardModel->move(boardModel->getPlayer()->y + 1, boardModel->getPlayer()->x);
        else if (Fl::event_key() == FL_Right)
            boardModel->move(boardModel->getPlayer()->y, boardModel->getPlayer()->x + 1);
        else if (Fl::event_key() == FL_Left)
            boardModel->move(boardModel->getPlayer()->y, boardModel->getPlayer()->x - 1);
        else if (Fl::event_key(97))
            boardModel->teleport();
        display->update();
        this->redraw();
    }

    if (Fl::event_inside(this->display) && event == FL_PUSH) // if user clicks on a cell
    {
        std::tuple<int, int> position = display->mouseClick(Point{Fl::event_x(), Fl::event_y()});
        this->boardModel->moveTo(std::get<1>(position), std::get<0>(position));
        display->update();
        this->redraw();
    }
    return Fl_Window::handle(event);
}

void MainWindow::windowCallback(Fl_Widget *widget, void *f)
{
    MainWindow *a = ((MainWindow *)f);
    widget->hide();
    a->boardModel->saveMinimumSteps();
}

void MainWindow::resetLevelCallback(Fl_Widget *w, void *f)
{

    MainWindow *a = ((MainWindow *)f);
    a->boardModel->setSteps(0);
    a->boardModel->createBoard(a->boardModel->readFileIntoString());
    a->display->update();
    a->redraw();
}

void MainWindow::changeLevelCallback(Fl_Widget *widget, void *f)
{
    MainWindow *mainWindow = ((MainWindow *)f);
    mainWindow->popUp->set_modal();
    mainWindow->popUp->show();
    while (mainWindow->popUp->shown())
        Fl::wait();
    Fl_Choice *levels = (Fl_Choice *)mainWindow->popUp->levels;
    int choice = levels->value();
    mainWindow->boardModel->saveMinimumSteps();
    switch (choice)
    {
    case -1:
        return;
    case 0:
        mainWindow->boardModel->setFilename(level1);
        break;
    case 1:
        mainWindow->boardModel->setFilename(level2);
        break;
    case 2:
        mainWindow->boardModel->setFilename(level3);
        break;
    case 3:
        mainWindow->boardModel->setFilename(level4);
        break;
    }
    mainWindow->boardModel->createBoard(mainWindow->boardModel->readFileIntoString());
    mainWindow->display->update();
    mainWindow->redraw();
}
void MainWindow::helpCallback(Fl_Widget *widget, void *f)
{
    MainWindow *mainWindow = ((MainWindow *)f);
    mainWindow->helpWindow->show();
}

void MainWindow::resetMinStepsCallback(Fl_Widget *w, void *f)
{
    MainWindow *mainWindow = ((MainWindow *)f);
    mainWindow->boardModel->setSteps(0);
    mainWindow->boardModel->saveMinimumSteps();
    mainWindow->redraw();
}
