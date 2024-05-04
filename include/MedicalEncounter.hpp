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

        std::set<Doctor> doctors;
        std::vector<HealthIssue> healthIssues;
        size_t id;

    public:
        MedicalEncounter() = default;
        MedicalEncounter(const Doctor& doctor);
        MedicalEncounter(const HealthIssue &issue);
        MedicalEncounter(const Doctor& doctor, const HealthIssue &issue, size_t id = 0);
        MedicalEncounter(const std::set<Doctor>& nDoctors, const std::vector<HealthIssue> &issue, size_t nId = 0);

        void addHealthIssue(const HealthIssue &issue) noexcept;
        void addDoctor(const Doctor& doctor) noexcept;
        size_t getId() const noexcept;

        void print() const noexcept;
        // void setFinished() noexcept;
        bool isDoctor(const Doctor & doc) const noexcept;
        // bool isFinished() const noexcept;

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
