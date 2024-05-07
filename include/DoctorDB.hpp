#pragma once
#include "DataBase.hpp"

namespace EHR
{
    class DoctorDB
    {
    private:
        DataBase &db;
    public: 
        DoctorDB(DataBase& nDb);
        
        Doctor createDoctor(const std::string& name) const noexcept;
        const std::set<Doctor> getDoctors() const noexcept;
        void addDoctor(const Doctor& doc) const noexcept;
        std::optional<Doctor> getDoctorByName(const std::string & name) const noexcept;
        void addDoctorToPatientEncounter(size_t patId, size_t docId, size_t issueId) const noexcept;
        void addDoctorEncounter(size_t docId, size_t issueId) const noexcept;
    };    
    
} // namespace EHR
