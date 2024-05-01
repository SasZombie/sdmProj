#pragma once
#include <iostream>
#include "Patient.hpp"
#include "HealthServicies.hpp"

namespace EHR
{
    class MainSystem
    {
    private:
        std::set<Patient> patients;
        std::set<Doctor> doctors;
        std::vector<MedicalEncounter> activeMedicalEncounters;
        std::vector<MedicalEncounter> archivedMedicalEncounters;
    public:
        MainSystem() = default;
        void addDoctor(const Doctor& doc) noexcept;

        void patienVisits(Patient& p, const Doctor& doc) noexcept;
        void healthServiciesPerformed(Patient &patien, const HealthServicies &healthServicies);

        void print() const noexcept;

        ~MainSystem() = default;
    };    
} // namespace EHR

