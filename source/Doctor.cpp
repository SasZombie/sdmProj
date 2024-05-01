#include "../include/Doctor.hpp"


size_t EHR::Doctor::getID() const noexcept
{
    return this->ID;
}
const std::string &EHR::Doctor::getName() const noexcept
{
    return this->name;
}