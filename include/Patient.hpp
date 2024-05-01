#pragma once
#include <vector>
#include <iostream>
#include <set>
#include "MedicalEncounter.hpp"
#include "Doctor.hpp"

namespace EHR
{
    class Patient
    {
    private:
        std::string name;

        std::vector<std::string> measuraments;
        std::set<std::string> prescriptions;        //Cant have 2 identical prescriptions

        std::set<HealthIssue> healthIssues;
        std::vector<MedicalEncounter> encounters;

    public:
        Patient() = default;
        template<typename T>
        requires SomeString<T>
        Patient(const T& nName)
            : name(nName)
        {
        }

        void print() const noexcept;

        void addMedicalEncounter(const MedicalEncounter& medEnc) noexcept;
        void addPrescription(const std::string &prescriotion) noexcept;
        void addDoctor(const Doctor &doc, MedicalEncounter& med) noexcept;
        void addMeasurament(const std::string &measure) noexcept;

        auto operator<=>(const Patient& other) const
        {
            return this->name <=> other.name;
        }

        bool operator==(const Patient& other) const
        {
            return this->name == other.name;
        }

        ~Patient() = default;
    };
    
} // namespace EHR
