#pragma once
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "Patient.hpp"
#include "HealthServicies.hpp"

namespace EHR
{
    class MainSystem
    {
    private:
        std::vector<Patient> patients;
        std::set<Doctor> doctors;
        std::vector<MedicalEncounter> activeMedicalEncounters;
        std::vector<MedicalEncounter> archivedMedicalEncounters;

        bool checkDoctor(const Doctor& doc) const noexcept;
        bool checkPatient(const Patient& pat) const noexcept;
        void deleteFromActive(const MedicalEncounter& med) noexcept;
    public:
        MainSystem() = default;
        void addDoctor(const Doctor& doc) noexcept;

        void patienVisits(Patient& p, const Doctor& doc) noexcept;

        void viewPatientData(const Patient &pat, const Doctor& doc) const noexcept;
        void viewPatientData(const Patient &pat) const noexcept;
        void deleteMedEnc(const MedicalEncounter& med, Patient &p) noexcept;
        void archiveMedEnc(const MedicalEncounter& med, Patient &p) noexcept;
        void healthServiciesPerformed(Patient &patien, const HealthServicies &healthServicies) noexcept;
        void signEncounter(const Doctor& doc, size_t pass, const MedicalEncounter &enc) noexcept;
        void print() const noexcept;

        void printPrescriptions(const std::string& pat) const noexcept;
        void markAsCompleted(Patient& pat) const noexcept;


        ~MainSystem() = default;
    };    
} // namespace EHR

