#include "../include/HealthIssue.hpp"

const std::string &EHR::HealthIssue::getName() const noexcept
{
    return this->name;
}
EHR::IssueType EHR::HealthIssue::getType() const noexcept
{
    return this->issueType;
}
size_t EHR::HealthIssue::getId() const noexcept 
{
    return this->id;
}