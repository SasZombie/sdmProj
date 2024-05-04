#include "../include/HealthIssue.hpp"

const std::string &EHR::HealthIssue::getName() const noexcept
{
    return this->name;
}
size_t EHR::HealthIssue::getId() const noexcept 
{
    return this->id;
}