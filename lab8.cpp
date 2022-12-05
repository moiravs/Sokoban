// These should include everything you might use
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <math.h>
#include <time.h>

#include <array>
#include <chrono>
#include <iostream>
#include <memory>  // shared_ptr
#include <string>
#include <vector>

#if __cplusplus >= 202002L
#include <numbers>
using std::numbers::pi;
#else
const double pi = 3.141592653589793238462643383279502884L;
#endif

using namespace std;

const int    windowWidth      = 500;
const int    windowHeight     = 500;
const double refreshPerSecond = 60;

struct Point {
  int x, y;
};

/*--------------------------------------------------
Sketchable class.

Base class for Rectangle, Cicrle and Animation
--------------------------------------------------*/
class Sketchable {
 public:
  virtual void  draw() = 0;
  virtual bool  contains(Point p) const = 0;
  virtual Point getCenter() const = 0;
  virtual ~Sketchable() {}
};

/*--------------------------------------------------
Rectangle class.

Use to display a filled-in rectangle on the screen
with different colors for the fill and the border
--------------------------------------------------*/
class Rectangle : public Sketchable {
  Point    center;
  int      w, h;
  Fl_Color fillColor, frameColor;

 public:
  Rectangle(Point center, int w, int h, Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE);
  void     draw() override;
  void     setFillColor(Fl_Color newFillColor);
  Fl_Color getFillColor() { return fillColor; }
  void     setFrameColor(Fl_Color newFrameColor);
  Fl_Color getFrameColor() { return frameColor; }
  void     setWidth(int neww) { w = neww; }
  void     setHeight(int newh) { h = newh; }
  int      getWidth() const { return w; }
  int      getHeight() const { return h; }
  bool     contains(Point p) const override;
  Point    getCenter() const override { return center; }
};

Rectangle::Rectangle(Point center, int w, int h, Fl_Color frameColor,
                     Fl_Color fillColor)
    : center{center},
      w{w},
      h{h},
      fillColor{fillColor},
      frameColor{frameColor} {}

void Rectangle::draw() {
  array<Point, 5> points{
      Point{center.x - w / 2, center.y - h / 2},
      Point{center.x - w / 2, center.y + h / 2},
      Point{center.x + w / 2, center.y + h / 2},
      Point{center.x + w / 2, center.y - h / 2},
      Point{center.x - w / 2, center.y - h / 2}
  };
  fl_color(fillColor);
  fl_begin_polygon();
  for (auto &point : points) {
    fl_vertex(point.x, point.y);
  }
  fl_end_polygon();
  fl_color(frameColor);
  fl_begin_line();
  for (auto &point : points) {
    fl_vertex(point.x, point.y);
  }
  fl_end_line();
}

void Rectangle::setFillColor(Fl_Color newFillColor) {
  fillColor = newFillColor;
}

void Rectangle::setFrameColor(Fl_Color newFrameColor) {
  frameColor = newFrameColor;
}

bool Rectangle::contains(Point p) const {
  return p.x >= center.x - w / 2 && p.x < center.x + w / 2 &&
         p.y >= center.y - h / 2 && p.y < center.y + h / 2;
}

/*--------------------------------------------------
Translation Class
--------------------------------------------------*/
struct Translation {
  explicit Translation(Point p) {
    fl_push_matrix();
    fl_translate(p.x, p.y);
  }
  ~Translation() { fl_pop_matrix(); }
};


/*--------------------------------------------------
Animation class

Base class for Spin and Bounce
--------------------------------------------------*/
class Animation : public Sketchable {
 protected:
  shared_ptr<Sketchable> toAnimate;

 public:
  explicit Animation(shared_ptr<Sketchable> toAnimate) : toAnimate{toAnimate} {}
  virtual bool isComplete() = 0;
  virtual void start() {
    // if toAnimate is also an animation then start it too
    shared_ptr<Animation> a = dynamic_pointer_cast<Animation>(toAnimate);
    if (a) a->start();
  }
  bool  contains(Point p) const override { return toAnimate->contains(p); }
  Point getCenter() const override { return toAnimate->getCenter(); }
};


/*--------------------------------------------------
Bounce Class
--------------------------------------------------*/
class Bounce : public Animation {
  int   duration;
  int   bounceHeight;
  bool  bouncing = false;
  int   time{0};
  Point currentTranslation();

 public:
  explicit Bounce(shared_ptr<Sketchable> clickableCellToAnimate, int duration = 100,
         int bounceHeight = 100)
      : Animation{clickableCellToAnimate},
        duration{duration},
        bounceHeight{bounceHeight} {}
  void draw() override;
  bool isComplete() override;
  void start() override {
    Animation::start();
    bouncing = true;
    time     = 0;
  }
};

void Bounce::draw() {
  if (bouncing) ++time;
  Translation t3{currentTranslation()};
  toAnimate->draw();
  if (isComplete()) {
    bouncing = false;
  }
}

Point Bounce::currentTranslation() {
  if (isComplete())
    return {0, 0};
  else
    return {0, static_cast<int>(-1 * bounceHeight * sin(pi * time / duration))};
}

bool Bounce::isComplete() { return time > duration; }

/*--------------------------------------------------
ClickableCell class

The Canvas class below will have ClickableCells as instance
variables and call the methods of ClickableCell
--------------------------------------------------*/
class ClickableCell {
  shared_ptr<Animation> animation;

 public:
  // Constructor
  explicit ClickableCell(shared_ptr<Animation> animation);

  // Methods that draw and handle events
  void draw();
  void mouseClick(Point mouseLoc);
};

ClickableCell::ClickableCell(shared_ptr<Animation> animation)
    : animation{animation} {}

void ClickableCell::draw() { animation->draw(); }

void ClickableCell::mouseClick(Point mouseLoc) {
  if (animation->contains(mouseLoc)) {
    animation->start();
  }
}

/*--------------------------------------------------
Canvas class.

One instance of the canvas class is made by the
MainWindow class.

The fltk system via MainWindow calls:

draw 60 times a second
mouseClick whenever the mouse is clicked
keyPressed whenever a key is pressed

Any drawing code should be called ONLY in draw
or methods called by draw. If you try to draw
elsewhere it will probably crash.
--------------------------------------------------*/
class Canvas {
  vector<ClickableCell> cells;

 public:
  Canvas();
  void draw();
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
};

Canvas::Canvas() {
  for (int x = 50; x < 500; x += 100) {
    cells.emplace_back(
        make_shared<Bounce>(make_shared<Rectangle>(Point{x, 300}, 35, 35)));
  }
}

void Canvas::draw() {
  for (auto &c : cells) {
    c.draw();
  }
}

void Canvas::mouseClick(Point mouseLoc) {
  for (auto &c : cells) c.mouseClick(mouseLoc);
}

void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'q':
      exit(0);
      break;
    default: {
    }  // pass (normal)
  }
}

/*--------------------------------------------------
MainWindow class.

Do not edit!!!!
--------------------------------------------------*/
class MainWindow : public Fl_Window {
  Canvas canvas;

 public:
  MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Lab 8") {
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    resizable(this);
  }
  void draw() override {
    Fl_Window::draw();
    canvas.draw();
  }
  int handle(int event) override {
    switch (event) {
      case FL_PUSH:
        canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      case FL_KEYDOWN:
        canvas.keyPressed(Fl::event_key());
        return 1;
      default:
        return 0;
    }
    return 0;
  }
  static void Timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow *>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
  }
};

/*--------------------------------------------------
main

Do not edit!!!!
--------------------------------------------------*/
int main(int argc, char *argv[]) {
  MainWindow window;
  window.show(argc, argv);
  return Fl::run();
}
