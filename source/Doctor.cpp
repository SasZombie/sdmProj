#include "../include/Doctor.hpp"

void EHR::Doctor::setSignature(size_t nSig) noexcept
{
    this->signature = nSig;
}
size_t EHR::Doctor::getSignature() const noexcept
{
    return this->signature;
}
const std::string &EHR::Doctor::getName() const noexcept
{
    return this->name;
}