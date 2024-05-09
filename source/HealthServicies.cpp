#include "../include/HealthServicies.hpp"

EHR::HealthServicies::HealthServicies(const HealthServiceType type, const std::string &desc, const HealthIssue &nmed) noexcept
 : hsType(type), description(desc), med(nmed)
{
    toGetFromData = false;
}
EHR::HealthServicies::HealthServicies(const HealthServiceType type, const std::string &desc, const std::string &issueName) noexcept 
    : hsType(type), description(desc), healthIssueName(issueName)
{
    toGetFromData = true;
}

EHR::HealthServiceType EHR::HealthServicies::getType() const noexcept
{
    return this->hsType;
}

const std::string &EHR::HealthServicies::getDescritpion() const noexcept
{
    return this->description;
}

const EHR::HealthIssue & EHR::HealthServicies::getIssue() const noexcept
{
    return this->med;
}

bool EHR::HealthServicies::toGetFromDataBase() const noexcept
{
    return toGetFromData;
}
