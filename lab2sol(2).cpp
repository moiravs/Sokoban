
// These should include everything you might use
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

const int windowWidth = 500;
const int windowHeight = 500;
const double refreshPerSecond = 60;


class Canvas {
  vector<Cell> cells;
 public:
  Canvas();
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int /*keyCode*/) {
    exit(0);
  }
};


Canvas::Canvas() {
  for (int i = 0; i < 100; i++)
    cells.push_back(Cell{Point{50*(i%10)+25, 50*(i/10)+25}, 40, 40});
// You could also write:
//  cells.push_back({Point{50*(i%10)+25, 50*(i/10)+25}, 40, 40});
//  cells.push_back({{50*(i%10)+25,50*(i/10)+25},40,40});
}
void Canvas::draw() {
  for (auto &c:cells) c.draw();
}
void Canvas::mouseMove(Point mouseLoc) {
  for (auto &c:cells) c.mouseMove(mouseLoc);
}
void Canvas::mouseClick(Point mouseLoc) {
  for (auto &c:cells) c.mouseClick(mouseLoc);
}

/* ------ DO NOT EDIT BELOW HERE (FOR NOW) ------ */

int main(int argc, char *argv[]) {
  MainWindow window;
  window.show(argc, argv);
  return Fl::run();
}
