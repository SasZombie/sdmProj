#pragma once
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "Patient.hpp"
#include "HealthServicies.hpp"
#include "DataBase.hpp"


namespace EHR
{
    class MainSystem
    {
    private:
        DataBase dataBase;

        bool checkDoctor(const Doctor& doc) const noexcept;
        bool checkPatient(const Patient& pat) const noexcept;
        bool checkPatient(const std::string &name) const noexcept;

    public:
        MainSystem(const std::string& schema) noexcept;
        
        std::optional<EHR::Doctor> createAndGet(const std::string& name) const noexcept;

        void addDoctor(const Doctor& doc) noexcept;
        void addDoctor(const std::string& name) noexcept;

        void patienVisits(const std::string& pName, const std::string& docName) noexcept;

        void addHealthIssue(const std::string& name, const std::string &docName, const std::string &issueName, IssueType iType) const noexcept;


        void viewPatientData(const Patient &pat, const Doctor& doc) const noexcept;
        void viewPatientData(const Patient &pat) const noexcept;
        void healthServiciesPerformed(const std::string &patien, const HealthServicies &healthServicies) const noexcept;

        void signEncounter(const Doctor& doc, size_t pass, const MedicalEncounter &enc) noexcept;
        void print() const noexcept;

        void printPrescriptions(const std::string& pat) noexcept;
        void signEncounterCorrect(size_t digitalSignature, const std::string& pat) const noexcept;
        void signEncounterIncorrect(size_t digitalSignature, const std::string& pat) const noexcept;


        ~MainSystem() = default;
    };    
} // namespace EHR

