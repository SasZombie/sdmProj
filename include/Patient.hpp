#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <set>
#include "MedicalEncounter.hpp"
#include "Doctor.hpp"

namespace EHR
{
    struct Prescription
    {
        bool isCompleted = false;
        std::string name;

        size_t id = 0;

        auto operator<=>(const Prescription& other) const
        {
            return this->name <=> other.name;
        }

        bool operator==(const Prescription& other) const
        {
            return this->name == other.name;
        }

    };
    

    class Patient
    {
    private:
        std::string name;
        size_t id;

        std::vector<std::string> measuraments;
        std::vector<Prescription> prescriptions; 
        std::vector<HealthIssue> healthIssues;
        // std::vector<MedicalEncounter> encounters;
        MedicalEncounter encounter;

    public:
        Patient() noexcept = default;
        template<typename T>
        requires SomeString<T>
        Patient(const T& nName, size_t nid, const std::vector<std::string>& nMeasure, 
                        const std::vector<Prescription> prescp, const std::vector<HealthIssue> & nhealthIssues, const MedicalEncounter& nMed) noexcept
            : name(nName), id(nid), measuraments(nMeasure), prescriptions(prescp), healthIssues(nhealthIssues), encounter(nMed)
        {
        }

        template<typename T>
        requires SomeString<T>
        explicit Patient(const T& nName) noexcept
            : name(nName)
        {
        }

        //Copy Constructor
        Patient(const Patient& other) noexcept;

        // Move constructor
        Patient(Patient&& other) noexcept;

        Patient& operator=(Patient&& other) noexcept;
        
        std::string print() const noexcept;

        void addMedicalEncounter(const MedicalEncounter& medEnc) noexcept;
        void addPrescription(const std::string &prescriotion) noexcept;
        void addDoctor(const Doctor &doc, MedicalEncounter& med) noexcept;
        void addMeasurament(const std::string &measure) noexcept;
        bool addHealthIssue(const HealthIssue &issue) noexcept;
        void setPrescriptionStatus(const Prescription& prep) noexcept;

        const std::string getMeasuraments() const noexcept;
        std::string getPrescriptionIDs() const noexcept;
        std::string getHealthIssuesIDs() const noexcept;
        const MedicalEncounter & getMedEnc() const noexcept;
        const std::vector<Prescription> & getPrescriptions() const noexcept; 
        const std::string &getName() const noexcept;
        size_t getId() const noexcept;


        auto operator<=>(const Patient& other) const
        {
            return this->name <=> other.name;
        }

        bool operator==(const Patient& other) const
        {
            return this->name == other.name;
        }

        ~Patient() noexcept = default;
    };
    
} // namespace EHR
