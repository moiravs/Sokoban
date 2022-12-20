
#ifndef BOX_HPP
#define BOX_HPP
class Box
{
    int x;
    int y;
    int color;
    bool light = false;
    bool blocked = false;

public:
    Box(int x, int y) : x{x}, y{y}{}
    int getColor(){
        return this->color;
    }
    void setColor(int color){
        this->color = color;
    }
    void setLight(bool light){
        this->light = true;
    }
    bool getLight(){
        return this->light;
    }
    void setBlocked(bool blocked){
        this->blocked = true;
    }
    bool getBlocked(){
        return this->blocked;
    }
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    bool operator==(const Box &) const;
    int operator<(Box box){
        if (x == box.x){
            return y < box.y;
        }
        else 
            return x < box.x;
    }
};
#endif