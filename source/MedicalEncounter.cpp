#include "../include/MedicalEncounter.hpp"

EHR::MedicalEncounter::MedicalEncounter(const Doctor &doctor, const HealthIssue &issue, size_t nId)
    : id(nId)
{
    this->doctors.insert(doctor);
    this->healthIssues.emplace_back(issue);
}

EHR::MedicalEncounter::MedicalEncounter(const HealthIssue &issue)
{
    this->healthIssues.emplace_back(issue);
}


EHR::MedicalEncounter::MedicalEncounter(const Doctor &doctor)
{
    this->doctors.insert(doctor);
}

EHR::MedicalEncounter::MedicalEncounter(const std::set<Doctor>& nDoctors, const std::vector<HealthIssue> &issue, size_t nId)
    :doctors(nDoctors), healthIssues(issue), id(nId)
{

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
    // for(const auto &hi : this->healthIssues)
    // {
    //     std::cout << hi. << ' ';
    // }

}
// void EHR::MedicalEncounter::setFinished() noexcept
// {
//     this->finished = true;
// }

bool EHR::MedicalEncounter::isDoctor(const Doctor &doc) const noexcept
{
    auto it = this->doctors.find(doc);
    return (it != this->doctors.end());
}

void EHR::MedicalEncounter::addHealthIssue(const HealthIssue &issue) noexcept
{
    this->healthIssues.emplace_back(issue);
}


