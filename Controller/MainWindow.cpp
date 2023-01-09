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
    // Initialization of the buttons
    Fl_Button *reset = new Fl_Button(RESET_X, RESET_Y, RESET_W, RESET_H, "Reset Level");
    Fl_Button *resetMinSteps = new Fl_Button(RESET_BEST_SCORE_X, RESET_BEST_SCORE_Y, RESET_BEST_SCORE_W, RESET_BEST_SCORE_H, "Reset Min Steps");
    Fl_Button *levels = new Fl_Button(CHOICE_X, CHOICE_Y, CHOICE_W, CHOICE_H, "Levels");
    Fl_Button *help = new Fl_Button(HELP_X, HELP_Y, HELP_W, HELP_H, "Help");
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
            std::string wonString = "You won with " + std::to_string(boardModel->getStepsLimit() - boardModel->getSteps()) + " steps left, reset or change level";
            fl_draw(wonString.c_str(), PARTY_WON_X, PARTY_WON_Y);
            this->boardModel->saveBestScore();
        }
        else
        {
            fl_draw("You lose, reset or change level", PARTY_WON_X, PARTY_WON_Y);
        }
    }
    fl_font(Fl_Font(1), 16);
    std::string steps = "Steps : " + std::to_string(this->boardModel->getSteps());
    fl_draw(steps.c_str(), PAS_X, PAS_Y);
    std::string stepsLimit = "Steps limit : " + std::to_string(this->boardModel->getStepsLimit());
    fl_draw(stepsLimit.c_str(), STEPS_LIMIT_X, STEPS_LIMIT_Y);
    std::string bestScore = "Minimum Steps : " + std::to_string(this->boardModel->getMinimumSteps());
    fl_draw(bestScore.c_str(), MIN_STEPS_X, MIN_STEPS_Y);
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
    mainWindow->helpWindow->help = false;
    mainWindow->helpWindow->set_modal();
    mainWindow->helpWindow->show();
    while (mainWindow->helpWindow->shown())
        Fl::wait();
    Fl_Choice *levels = (Fl_Choice *)mainWindow->helpWindow->levels;
    int choice = levels->value();
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
    mainWindow->helpWindow->help = true;
    mainWindow->helpWindow->show();
}

void MainWindow::resetMinStepsCallback(Fl_Widget *w, void *f)
{
    MainWindow *mainWindow = static_cast<MainWindow *>(f);
    mainWindow->boardModel->setSteps(0);
    mainWindow->boardModel->saveBestScore();
    mainWindow->redraw();
}
