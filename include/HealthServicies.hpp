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
        bool wasCompleted;
        HealthServiceType hsType;
        std::string description;
        HealthIssue med;
        
    public:
        HealthServicies(const HealthServiceType type, const std::string &desc, const HealthIssue &med = {}); 

        HealthServiceType getType() const noexcept;
        const std::string & getDescritpion() const noexcept;
        const HealthIssue & getIssue() const noexcept;       

        ~HealthServicies() = default;
    };
} // namespace EHR
