#include "../include/Doctor.hpp"


size_t EHR::Doctor::getSignature() const noexcept
{
    return this->signature;
}
const std::string &EHR::Doctor::getName() const noexcept
{
    return this->name;
}