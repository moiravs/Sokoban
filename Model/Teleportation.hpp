#include "LogicCell.hpp"

class Teleportation;

class Teleportation 
{
    bool other_end_blocked;
    bool teleportation_done = false;
    size_t line, column;
    Teleportation *other_end;
public:
    Teleportation(size_t line, size_t column, Teleportation *other_end):line{this->line}, column{this->column}, other_end{this->other_end}{};

    Teleportation get_other_end();
    bool is_done();
    void set_activity(bool activity);
};