
#include "InterfaceGraphique.hpp"



Cell::Cell(Point center, int type, int w, int h) : center{center}, type{type}, w{w}, h{h}
{
    this->personnage = new Fl_JPEG_Image("Textures/Test.jpeg");
    this->wall = new Fl_PNG_Image("Textures/wall.png");
}

void Cell::draw()
{
    if (type == PLAYER)
    {
        Fl_Image *hihi = this->personnage;
        hihi->draw(center.x - w / 2, center.y - h / 2, w, h);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, FL_BLUE);
    }
    else if (type == BOX)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_GREEN);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
    else if (type == EMPTY)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_RED);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
    else if (type == WALL)
    {
        Fl_Image *picture = this->wall;
        picture->draw(center.x - w / 2, center.y - h / 2, w, h);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
    else if (type == BOX_FINAL_POS)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_YELLOW);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
}

bool Cell::mouseClick(Point mouseLoc)
{

    //if (r.contains(mouseLoc))
    //{
      //  return true;
    //}
}

void DisplayBoard::draw()
{
    for (auto &c : cells)
        c.draw();

    std::string pas = "pas " + std::to_string(this->boardmodel->pas);
    fl_draw(pas.c_str(), pasx, pasy);
    std::string limitpas = "limite de pas " + std::to_string(this->boardmodel->limitpas);
    fl_draw(limitpas.c_str(), limitpasx, limitpasy);
}

DisplayBoard::DisplayBoard(std::shared_ptr<BoardModel> board) : Fl_Box(boardx, boardy, boardw, boardh)
{
    this->boardmodel = board;
    this->update();
}

void DisplayBoard::printBoard()
{
    for (size_t i = 0; i < boardmodel->getBoard().size(); i++)
    {
        for (size_t j = 0; j < boardmodel->getBoard()[0].size(); j++)
        {
            std::cout << boardmodel->getBoard()[i][j] << " ";
        }
        std::cout << "\n";
    }
}
void DisplayBoard::mouseClick(Point mouseLoc)
{
    /*
    for (size_t i = 0; i < cells.size(); i++)
    {
        if (c.mouseClick(mouseLoc) == true)
        {
        };
    }*/
}

void DisplayBoard::update()
{
    cells.clear();
    for (size_t y = 0; y < boardmodel->getBoard().size(); y++)
    {
        for (size_t x = 0; x < boardmodel->getBoard()[y].size(); x++)
        {
            if (boardmodel->getBoard()[y][x] == EMPTY)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, EMPTY, 50, 50});
            }
            else if (boardmodel->getBoard()[y][x] == PLAYER)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, PLAYER, 50, 50});
            }
            else if (boardmodel->getBoard()[y][x] == BOX)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, BOX, 50, 50});
            }
            else if (boardmodel->getBoard()[y][x] == WALL)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, WALL, 50, 50});
            }
            else if (boardmodel->getBoard()[y][x] == BOX_FINAL_POS)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, BOX_FINAL_POS, 50, 50});
            }
        }
    }
}

MainWindow::MainWindow(std::shared_ptr<BoardModel> boardModel) : Fl_Window(500, 500, windowWidth, windowHeight, "Lab 2")
{
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    resizable(this);
    this->boardModel = boardModel;
    DisplayBoard *board = new DisplayBoard(boardModel);
    display = board;
    board->show();
    ControllerBoard *boarda = new ControllerBoard(boardModel);
    control = boarda;
    Fl_Button *reset = new Fl_Button(resetx, resety, resetw, reseth);
    this->reset = reset;
    Fl_Choice *levels = new Fl_Choice(choicex, choicey, choicew, choicey);
    levels->add("Level 1");
    levels->add("Level 2");
    this->levels = levels;

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
            fl_draw("YOU WON, reset or change level", limitpasx + 50, limitpasy + 50);
        }
        else
        {
            fl_draw("YOU LOSE, reset or change level", limitpasx + 50, limitpasy + 50);
        }
    }
}

int MainWindow::handle(int event)
{

    if (event == FL_KEYBOARD)
    {
        control->board_handle(event);
        display->update();
    }

    if (Fl::event_inside(this->display)) // if event inside board
    {
        if (event == FL_PUSH)
        {
            display->mouseClick(Point{Fl::event_x(), Fl::event_y()});

            // control->board_handle(event);
            return 1;
        }
    }
    if (Fl::event_inside(this->reset)) // if event inside board
    {
        if (event == FL_PUSH)
        {
            control->reset_handle();
            display->update();
        }
    }
    if (Fl::event_inside(this->levels)) // if event inside board
    {
        if (event == FL_PUSH)
        {
            int i = this->levels->value();
            control->level_change(i);
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