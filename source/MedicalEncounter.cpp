#include "../include/MedicalEncounter.hpp"

EHR::MedicalEncounter::MedicalEncounter(const Doctor &doctor, const HealthIssue &issue, size_t nId) noexcept
    : id(nId)
{
    this->doctors.insert(doctor);
    this->healthIssues.emplace_back(issue);
}

EHR::MedicalEncounter::MedicalEncounter(const HealthIssue &issue, size_t nId) noexcept
    : id(nId)
{
    this->healthIssues.emplace_back(issue);
}


EHR::MedicalEncounter::MedicalEncounter(const Doctor &doctor, size_t nId) noexcept
    : id(nId)
{
    this->doctors.insert(doctor);
}

EHR::MedicalEncounter::MedicalEncounter(const std::set<Doctor>& nDoctors, const std::vector<HealthIssue> &issue, size_t nId) noexcept
    :doctors(nDoctors), healthIssues(issue), id(nId)
{

}

EHR::MedicalEncounter::MedicalEncounter(const MedicalEncounter& other) noexcept
    : doctors(other.doctors), healthIssues(other.healthIssues), id(other.id)
{

}

EHR::MedicalEncounter::MedicalEncounter(MedicalEncounter&& other) noexcept
    : doctors(std::move(other.doctors)), healthIssues(std::move(other.healthIssues)), id(std::exchange(other.id, 0))
{

}

EHR::MedicalEncounter& EHR::MedicalEncounter::operator=(const MedicalEncounter& other) noexcept
{
    if (this != &other) 
    {
        doctors = other.doctors;
        healthIssues = other.healthIssues;
        id = other.id;
    }
    return *this;
}


void EHR::MedicalEncounter::addDoctor(const Doctor &doctor) noexcept
{
    this->doctors.insert(doctor);
}

size_t EHR::MedicalEncounter::getId() const noexcept
{
    return this->id;
}
void EHR::MedicalEncounter::print() const noexcept
{
    for(const auto &doc : doctors)
    {
        std::cout << doc.getName() << ' ';
    }
    std::cout << "\n---------------------\n";

}

bool EHR::MedicalEncounter::isDoctor(const Doctor &doc) const noexcept
{
    auto it = this->doctors.find(doc);
    return (it != this->doctors.end());
}

void EHR::MedicalEncounter::addHealthIssue(const HealthIssue &issue) noexcept
{
    this->healthIssues.emplace_back(issue);
}


