#include "LogicCell.hpp"

class Teleportation;

class Teleportation: public LogicCell 
{
    bool other_end_blocked;
    bool teleportation_done = false;
    size_t line, column;
    Teleportation *other_end;
public:
    Teleportation(size_t line, size_t column, Teleportation *other_end):LogicCell(this->line, this->column, LogicCell::cellType::Teleportation), 
        line{this->line}, column{this->column}, other_end{this->other_end}{};

    Teleportation get_other_end();
    bool is_done();
    void set_done();
};