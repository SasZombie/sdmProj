#pragma once
#include <set>
#include <optional>
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

        std::vector<std::string> divByLines(const std::string & str) const noexcept; 
        std::vector<Prescription> getAllPrescriptions(const std::string &prescId) const noexcept;
        std::set<HealthIssue> getAllIssues(const std::string &healthId) const noexcept;
    public:
        DataBase();

        //Doctors
        const std::set<Doctor> getDoctors() const noexcept;
        void addDoctor(const Doctor& doc) const noexcept;
        std::optional<Doctor> getDoctorByName(const std::string & name) const noexcept;
        //Patients

        const std::set<Patient> getPatients() const noexcept;
        void addPatient(const Patient& pat) const noexcept;
        void uppdatePatientPrescription(const Patient& prep) const noexcept;
        std::optional<Patient> getPatientByName(const std::string & name) const noexcept;

        //Encounters
        const std::set<MedicalEncounter> getEncounters() const noexcept;
        void addEncounter(const MedicalEncounter& med) const noexcept;
        void uppdateEncounter(const MedicalEncounter& med) const noexcept;
        std::optional<MedicalEncounter> getEncounterById(size_t id) const noexcept;


        ~DataBase();
    };
} // namespace EHR

