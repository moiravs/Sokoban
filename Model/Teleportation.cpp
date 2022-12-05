#include "Teleportation.hpp"
#include "LogicCell.hpp"

LogicCell * Teleportation::get_second_end()
{
    return this->second_end;
}
LogicCell *Teleportation::get_first_end()
{
    return this->first_end;
}
bool Teleportation::is_done()
{
    return this->teleportation_done;
}

void Teleportation::set_activity(bool activity)
{
    if (!(this->teleportation_done == activity))
        this->teleportation_done = activity;
}