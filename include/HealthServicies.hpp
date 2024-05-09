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
        bool toGetFromData;
        HealthServiceType hsType;
        std::string description;
        std::string healthIssueName;
        HealthIssue med;
        
    public:
    
        HealthServicies(const HealthServiceType type, const std::string &desc, const std::string& issueName) noexcept; 
        HealthServicies(const HealthServiceType type, const std::string &desc, const HealthIssue &med = {}) noexcept; 

        HealthServiceType getType() const noexcept;
        const std::string & getDescritpion() const noexcept;
        const HealthIssue & getIssue() const noexcept;       
        bool toGetFromDataBase() const noexcept;
        ~HealthServicies() = default;
    };
} // namespace EHR
