#pragma once
#include <set>
#include <optional>
#include <sstream>
#include "Patient.hpp"
#include "Doctor.hpp"
#include "../connector/include/mysql/jdbc.h"

namespace EHR
{
    class DataBase
    {
    private:
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection *con = driver->connect("tcp://127.0.0.1:3306", "root", "1");

        std::vector<std::string> divByLines(const std::string & str, char delimiter) const noexcept; 
        std::vector<Prescription> getAllPrescriptions(const std::string &prescId) const noexcept;
        std::vector<HealthIssue> getAllIssues(const std::string &healthId) const noexcept;
        std::set<Doctor> getAllDoctorsByID(const std::string &doctorIDs) const noexcept;

    public:
        DataBase(const std::string &schema) noexcept;
    
        //Doctors
        Doctor createDoctor(const std::string& name) const noexcept;
        const std::set<Doctor> getDoctors() const noexcept;
        void addDoctor(const Doctor& doc) const noexcept;
        std::optional<Doctor> getDoctorByName(const std::string & name) const noexcept;
        void addDoctorToPatientEncounter(size_t patId, size_t docId, size_t issueId) const noexcept;
        void addDoctorEncounter(size_t docId, size_t issueId) const noexcept;


        //Patients
        const std::set<Patient> getPatients() const noexcept;
        void createPatient(const std::string &name, size_t medEncId) const noexcept;
        void addPatient(const Patient& pat) const noexcept;
        void uppdatePatient(const Patient& pat) const noexcept;
        void uppdatePatient(const std::string &name, size_t medEncId) const noexcept;
        void uppdatePatientPrescription(const std::vector<size_t> &prescID) const noexcept;
        std::optional<Patient> getPatientByName(const std::string & name) const noexcept;

        //Encounters
        MedicalEncounter createMedEncounter(const Doctor& docr) const noexcept;
        const std::vector<MedicalEncounter> getEncounters() const noexcept;
        std::optional<MedicalEncounter> getEncounterById(size_t id) const noexcept;
        void signEncounter(size_t docID, size_t encID) const noexcept;
        void archiveEncounter(const std::string& pat) const noexcept;
        void deleteEncounter(size_t patID) const noexcept;


        //HealthIssues
        HealthIssue createHealthIssue(const std::string &issueName, IssueType iType) const noexcept;
        void addHealthIssueToPatient(const Patient& pat, const HealthIssue& issue) const noexcept;
        void addHealthIssueToMedicalEncounter(const Patient& pat, const HealthIssue& issue) const noexcept;


        //Health Servicies
        size_t createAndGetPrescription(const std::string & str) const noexcept;
        void addMeasurement(const Patient& pat, const std::string & str) const noexcept;
        void addPrescription(const Patient& pat, size_t prescID) const noexcept;

        ~DataBase();
    };
} // namespace EHR

