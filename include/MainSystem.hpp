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

        bool checkDoctor(const Doctor& doc) const noexcept;
        bool checkPatient(const Patient& pat) const noexcept;
    public:
        MainSystem() = default;
        void addDoctor(const Doctor& doc) noexcept;

        void patienVisits(Patient& p, const Doctor& doc) noexcept;

        //
        void deleteMedEnc(const MedicalEncounter& med, Patient &p) noexcept;
        void archiveMedEnc(const MedicalEncounter& med, Patient &p) noexcept;
        void healthServiciesPerformed(Patient &patien, const HealthServicies &healthServicies) noexcept;
        void signEncounter(const Doctor& doc, size_t pass, const MedicalEncounter &enc) noexcept;
        void print() const noexcept;

        ~MainSystem() = default;
    };    
} // namespace EHR

