#include "MainWindow.hpp"

MainWindow::MainWindow(std::shared_ptr<BoardModel > boardModel) : Fl_Window(500, 500, windowWidth, windowHeight, "Lab 2")
{
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    resizable(this);

    this->boardModel = boardModel;
    DisplayBoard *board = new DisplayBoard(boardModel);
    display = board;
    board->show();
    ControllerBoard *boarda = new ControllerBoard(boardModel);
    control = boarda;
    //TODO :auto ptr1 = reinterpret_cast<void *>(&this->boardModel);
    Fl_Button *reset = new Fl_Button(resetx, resety, resetw, reseth, "reset level");
    this->reset = reset;

    Fl_Button *custom = new Fl_Button(customx, customy, customw, customh);
    this->custom = custom;
    Fl_Button *resetminpas = new Fl_Button(resetminpasx, resetminpasy, resetminpasw, resetminpash, "reset min pas");
    this->resetminpas = resetminpas;
    Fl_Choice *levels = new Fl_Choice(choicex, choicey, choicew, choicey, "levels");
    levels->add("Level 1");
    levels->add("Level 2");
    levels->add("Level 3");
    this->levels = levels;

    this->callback(this->window_cb);
    std::shared_ptr<void> spVoid = this->boardModel;
    this->reset->callback(reset_level_cb, &spVoid);
    this->levels->callback(level_change, &spVoid);
    Fl_Menu_Bar *menu = new Fl_Menu_Bar(0, 0, 400, 25); // Create menubar, items..
    menu->add("&File/&Open", "^o", MyMenuCallback);
    menu->add("&File/&Save", "^s", MyMenuCallback, 0, FL_MENU_DIVIDER);
    menu->add("&File/&Quit", "^q", MyMenuCallback);
    menu->add("&Edit/&Copy", "^c", MyMenuCallback);
    menu->add("&Edit/&Paste", "^v", MyMenuCallback, 0, FL_MENU_DIVIDER);
    menu->add("&Edit/Radio 1", 0, MyMenuCallback, 0, FL_MENU_RADIO);
    menu->add("&Edit/Radio 2", 0, MyMenuCallback, 0, FL_MENU_RADIO | FL_MENU_DIVIDER);
    menu->add("&Edit/Toggle 1", 0, MyMenuCallback, 0, FL_MENU_TOGGLE);                 // Default: off
    menu->add("&Edit/Toggle 2", 0, MyMenuCallback, 0, FL_MENU_TOGGLE);                 // Default: off
    menu->add("&Edit/Toggle 3", 0, MyMenuCallback, 0, FL_MENU_TOGGLE | FL_MENU_VALUE); // Default: on
}

void MainWindow::MyMenuCallback(Fl_Widget *w, void *)
{
    Fl_Menu_Bar *bar = (Fl_Menu_Bar *)w;      // Get the menubar widget
    const Fl_Menu_Item *item = bar->mvalue(); // Get the menu item that was picked

    char ipath[256];
    bar->item_pathname(ipath, sizeof(ipath)); // Get full pathname of picked item

    fprintf(stderr, "callback: You picked '%s'", item->label()); // Print item picked
    fprintf(stderr, ", item_pathname() is '%s'", ipath);         // ..and full pathname

    if (item->flags & (FL_MENU_RADIO | FL_MENU_TOGGLE))
    {                                                                   // Toggle or radio item?
        fprintf(stderr, ", value is %s", item->value() ? "on" : "off"); // Print item's value
    }
    fprintf(stderr, "\n");
    if (strcmp(item->label(), "&Quit") == 0)
    {
        exit(0);
    }
}

void MainWindow::draw()
{
    Fl_Window::draw();
    if (this->boardModel->endofparty == true)
    {
        if (this->boardModel->winorlose == true)
        {
            std::string wonstring = "YOU WON with " + std::to_string(boardModel->limitpas - boardModel->pas) + " pas restants, reset or change level";
            fl_draw(wonstring.c_str(), limitpasx + 50, limitpasy + 50);
        }
        else
        {
            fl_draw("YOU LOSE, reset or change level", limitpasx + 50, limitpasy + 50);
        }
    }
}

int MainWindow::handle(int event)
{

    if (boardModel->endofparty == false)
    {
        if (event == FL_KEYBOARD)
        {

            control->board_handle(event);
            display->update();
        }
    }

    if (Fl::event_inside(this)) // if event inside board
    {
        if (event == FL_PUSH)
        {
            //display->mouseClick(Point{Fl::event_x(), Fl::event_y()});
            display->update();
            // control->board_handle(event);
        }
    }
    if (Fl::event_inside(this->custom)) // if event inside board
    {
        if (event == FL_PUSH)
        {
            control->custom_handle();
            display->update();
        }
    }
    if (Fl::event_inside(this->resetminpas)) // if event inside board
    {
        if (event == FL_PUSH)
        {
            control->resetminpas();
            display->update();
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

void MainWindow::window_cb(Fl_Widget *widget, void * )
{
    //ControllerBoard * boardcontrol = (ControllerBoard *) controllerboard;
    widget->hide();
    //boardcontrol->saveminpas();
}

void MainWindow::reset_level_cb(Fl_Widget *widget, void *board_Model)
{
    auto ptr2 = *reinterpret_cast<std::shared_ptr<BoardModel> *>(board_Model);
    ptr2->pas = 0;
    std::cout << &ptr2 << std::endl;
    ptr2->endofparty = false;
    std::string aer = ptr2->readFileIntoString();
    ptr2->createBoard(aer);
    puts("blu");
}

void MainWindow::level_change(Fl_Widget *widget, void * board_Model){
    BoardModel * boardModel = (BoardModel*)board_Model;
    Fl_Choice * levels = (Fl_Choice *) widget;
    int choice = levels->value();
    //this->saveminpas();
    //TODO : saveminpas
    std::cout << choice << std::endl;
    boardModel->endofparty = false;
    switch (choice)
    {
    case -1:
        return;
    case 0:
        boardModel->filename = level1;
        break;
    case 1:
        boardModel->filename = level2;
        break;
    case 2:
        boardModel->filename = level3;
        break;
    }
    std::string buffer = boardModel->readFileIntoString();
    std::cout << buffer << std::endl;
    std::cout << boardModel->filename << std::endl;
    boardModel->createBoard(buffer);
}
