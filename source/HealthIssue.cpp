#include "../include/HealthIssue.hpp"

const std::string &EHR::HealthIssue::getName() const noexcept
{
    return this->name;
}