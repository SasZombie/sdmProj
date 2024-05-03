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
        std::vector<Prescription> prescriptions;        //Cant have 2 identical prescriptions

        std::set<HealthIssue> healthIssues;
        // std::vector<MedicalEncounter> encounters;
        MedicalEncounter encounter;

    public:
        Patient() = default;
        template<typename T>
        requires SomeString<T>
        Patient(const T& nName, size_t nid, const std::vector<std::string>& nMeasure, 
                        const std::vector<Prescription> prescp, const std::set<HealthIssue> & nhealthIssues, const MedicalEncounter& nMed)
            : name(nName), id(nid), measuraments(nMeasure), prescriptions(prescp), healthIssues(nhealthIssues), encounter(nMed)
        {
        }

        const MedicalEncounter & getMedEnc() const noexcept;
        const std::vector<Prescription> & getPrescriptions() const noexcept; 
        const std::string &getName() const noexcept;

        void print() const noexcept;

        void addMedicalEncounter(const MedicalEncounter& medEnc) noexcept;
        void addPrescription(const std::string &prescriotion) noexcept;
        void addDoctor(const Doctor &doc, MedicalEncounter& med) noexcept;
        void addMeasurament(const std::string &measure) noexcept;
        void addHealthIssue(const HealthIssue &issue) noexcept;
        void setPrescriptionStatus(const Prescription& prep) noexcept;



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
