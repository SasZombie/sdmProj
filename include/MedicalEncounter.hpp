#pragma once
#include <set>
#include <iostream>
#include <utility>
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
        MedicalEncounter(const Doctor& doctor, size_t nId = 0);
        MedicalEncounter(const HealthIssue &issue, size_t nId = 0);
        MedicalEncounter(const Doctor& doctor, const HealthIssue &issue, size_t nId = 0);
        MedicalEncounter(const std::set<Doctor>& nDoctors, const std::vector<HealthIssue> &issue, size_t nId = 0);

        //Copy constructor
        MedicalEncounter(const MedicalEncounter& other);

        // Move constructor
        MedicalEncounter(MedicalEncounter&& other) noexcept;
        // Copy assignment operator
        MedicalEncounter& operator=(const MedicalEncounter& other) noexcept;

        void addHealthIssue(const HealthIssue &issue) noexcept;
        void addDoctor(const Doctor& doctor) noexcept;
        size_t getId() const noexcept;

        void print() const noexcept;
        bool isDoctor(const Doctor & doc) const noexcept;

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
