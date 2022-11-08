#include "Canvas.hpp"



void Canvas::initialize()
{
    // This is called by the constructor but also by keyPressed to
    // reset whenver spacebar is called.

    // Until the last step when we needed to reset, this would be the constructor

    cells.clear(); // Needed to remove the cells if we are starting again

    for (unsigned short x = 0; x < 10; x++)
    {
        cells.push_back({});
        for (int y = 0; y < 10; y++)
            cells[x].push_back({{50 * x + 25, 50 * y + 25}, 40, 40});
    }

    // This computes the (pointers to) neighbors of each cell
    for (unsigned x = 0; x < 10; x++)
        for (unsigned y = 0; y < 10; y++)
        {
            std::vector<Cell *> neighbors;
            for (auto &shift : std::vector<Point>({
                     {-1, 0}, // The 8 neighbors relative to the cell
                     {-1, 1},
                     {0, 1},
                     {1, 1},
                     {1, 0},
                     {1, -1},
                     {0, -1},
                     {-1, -1},
                 }))
            {
                // check lower bounds
                if (!((x == 0 && shift.x == -1) || (y == 0 && shift.y == -1)))
                {
                    unsigned neighborx = static_cast<unsigned>(static_cast<int>(x) + shift.x);
                    unsigned neighbory = static_cast<unsigned>(static_cast<int>(y) + shift.y);
                    // check upper bounds
                    if (neighborx < cells.size() && neighbory < cells[neighborx].size())
                    {
                        neighbors.push_back(&cells[neighborx][neighbory]);
                    }
                }
                cells[x][y].setNeighbors(neighbors);
            }
        }
}

bool Canvas::bombExposed()
{
    // Is there a cell with a bomb that is exposed?
    for (auto &v : cells)
        for (auto &c : v)
            if (c.isVisible() && c.isBomb())
                return true;
    return false;
}

bool Canvas::solved()
{
    // Are all cells without bombs visible?
    for (auto &v : cells)
        for (auto &c : v)
        {
            if (c.isVisible() && c.isBomb())
                return false;
            if (!c.isVisible() && !c.isBomb())
                return false;
        }
    return true;
}

void Canvas::draw()
{
    for (auto &v : cells)
        for (auto &c : v)
        {
            // Replace draw here if you want to see what it should look like after task 2/3
            //            c.drawTaskTwo();
            //            c.drawTaskThree();
            c.draw();
        }
    // We need to check to see if we need to draw game over or you win
    if (bombExposed())
        textGameOver.draw();
    if (solved())
    {
        textYouWin.draw();
    }
}

void Canvas::mouseMove(Point mouseLoc)
{
    for (auto &v : cells)
        for (auto &c : v)
            c.mouseMove(mouseLoc);
}

void Canvas::mouseClick(Point mouseLoc)
{
    // We only respond to mouse clicks if the game is not over/won
    if (!bombExposed() && !solved())
    {
        for (auto &v : cells)
            for (auto &c : v)
                c.mouseClick(mouseLoc);
    }
}

void Canvas::keyPressed(int keyCode)
{
    switch (keyCode)
    {
    case ' ':
        initialize();
        break;
    case 'q':
        exit(0);
    default:
    {
    } // pass
    }
}