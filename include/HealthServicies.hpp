#pragma once
#include <string>
#include "MedicalEncounter.hpp"

namespace EHR
{
    enum class HealthServiceType
    {
        Refferal, Prescription, Measuraments
    };

    class HealthServicies
    {
    private:
        bool wasCorrect;
        HealthServiceType hsType;
        std::string description;
        MedicalEncounter med;
        
    public:
        HealthServicies(const HealthServiceType type, const std::string &desc, const MedicalEncounter &med = {}); 

        HealthServiceType getType() const noexcept;
        const std::string & getDescritpion() const noexcept;
        const MedicalEncounter & getEncounter() const noexcept;

        ~HealthServicies() = default;
    };
} // namespace EHR
