/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */

#include "MainWindow.hpp"

MainWindow::MainWindow(std::shared_ptr<BoardModel> boardModel, HelpWindow *helpWindow) : Fl_Window(500, 500, WINDOW_WIDTH, WINDOW_HEIGHT, "Sokoban"), boardModel{boardModel}, helpWindow{helpWindow}
{
    resizable(this);
    DisplayBoard *board = new DisplayBoard(boardModel);
    display = board;
    board->show();

    // Callback for the buttons
    help->callback(helpCallback, static_cast<void *>(this));
    this->callback(this->windowCallback, static_cast<void *>(this));
    reset->callback(resetLevelCallback, static_cast<void *>(this));
    levels->callback(changeLevelCallback, static_cast<void *>(this));
    resetMinSteps->callback(resetMinStepsCallback, static_cast<void *>(this));

    this->resizable(levels);
    this->resizable(resetMinSteps);
    this->resizable(reset);
    this->resizable(help);
}

MainWindow::~MainWindow()
{
    delete reset;
    delete levels;
    delete help;
    delete resetMinSteps;
    delete helpWindow;
    delete display;
}

void MainWindow::draw()
{
    Fl_Window::draw();
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
        if (std::get<1>(position) != -1 && std::get<0>(position) != -1)
        {
            this->boardModel->moveTo(std::get<1>(position), std::get<0>(position));
            display->update();

            this->redraw();
        }
    }
    return Fl_Window::handle(event);
}

void MainWindow::windowCallback(Fl_Widget *widget, void *f)
{
    MainWindow *mainWindow = static_cast<MainWindow *>(f);
    widget->hide();
    mainWindow->boardModel->saveBestScore();
}

void MainWindow::resetLevelCallback(Fl_Widget *w, void *f)
{

    MainWindow *mainWindow = static_cast<MainWindow *>(f);
    mainWindow->boardModel->setSteps(0);
    mainWindow->boardModel->createBoard(mainWindow->boardModel->readFileIntoString());
    mainWindow->display->update();
    mainWindow->redraw();
}

void MainWindow::changeLevelCallback(Fl_Widget *widget, void *f)
{
    MainWindow *mainWindow = static_cast<MainWindow *>(f);
    mainWindow->helpWindow->setHelp(false);
    mainWindow->helpWindow->set_modal();
    mainWindow->helpWindow->show();
    while (mainWindow->helpWindow->shown())
        Fl::wait();
    int choice = mainWindow->helpWindow->getLevelsValue();
    mainWindow->boardModel->saveBestScore();
    switch (choice)
    {
    case -1:
        return;
    case 0:
        mainWindow->boardModel->setFilename(LEVEL1);
        break;
    case 1:
        mainWindow->boardModel->setFilename(LEVEL2);
        break;
    case 2:
        mainWindow->boardModel->setFilename(LEVEL3);
        break;
    case 3:
        mainWindow->boardModel->setFilename(LEVEL4);
        break;
    }
    mainWindow->boardModel->createBoard(mainWindow->boardModel->readFileIntoString());
    mainWindow->display->update();
    mainWindow->redraw();
}
void MainWindow::helpCallback(Fl_Widget *widget, void *f)
{
    MainWindow *mainWindow = static_cast<MainWindow *>(f);
    mainWindow->helpWindow->setHelp(true);
    mainWindow->helpWindow->show();
}

void MainWindow::resetMinStepsCallback(Fl_Widget *w, void *f)
{
    MainWindow *mainWindow = static_cast<MainWindow *>(f);
    mainWindow->boardModel->setSteps(0);
    mainWindow->boardModel->saveBestScore();
    mainWindow->redraw();
}
