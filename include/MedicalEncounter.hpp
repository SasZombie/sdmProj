#pragma once
#include <set>
#include <iostream>
#include "Doctor.hpp"
#include "HealthIssue.hpp"

namespace EHR
{
    
    class MedicalEncounter
    {
    private:

        bool finished = false;
        std::set<Doctor> doctors;
        std::vector<HealthIssue> healthIssues;

    public:
        MedicalEncounter() = default;
        MedicalEncounter(const Doctor& doctor);
        MedicalEncounter(const HealthIssue &issue);
        MedicalEncounter(const Doctor& doctor, const HealthIssue &issue);

        void addHealthIssue(const HealthIssue &issue) noexcept;
        void addDoctor(const Doctor& doctor) noexcept;

        void print() const noexcept;
        void setFinished() noexcept;
        bool isFinished() const noexcept;

        auto operator<=>(const MedicalEncounter& other) const
        {
            return this->doctors <=> other.doctors;
        }
        bool operator==(const MedicalEncounter& other) const 
        {
            return doctors == other.doctors;
        }

        ~MedicalEncounter() = default;
    };  
    
} // namespace EHR
