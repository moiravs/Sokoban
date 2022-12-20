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