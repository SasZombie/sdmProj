#include "../include/HealthServicies.hpp"


EHR::HealthServicies::HealthServicies(const HealthServiceType type, const std::string &desc, const MedicalEncounter &nmed) 
    : hsType(type), description(desc), med(nmed)
{
}

EHR::HealthServiceType EHR::HealthServicies::getType() const noexcept
{
    return this->hsType;
}

const std::string &EHR::HealthServicies::getDescritpion() const noexcept
{
    return this->description;
}

const EHR::MedicalEncounter & EHR::HealthServicies::getEncounter() const noexcept
{
    return this->med;
}
