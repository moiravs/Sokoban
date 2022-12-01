#include "Teleportation.hpp"

Teleportation Teleportation::get_other_end()
{
    return *this->other_end;
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