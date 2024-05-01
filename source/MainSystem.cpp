#include "../include/MainSystem.hpp"


void EHR::MainSystem::patienVisits(Patient &p, const Doctor &doc) noexcept
{
    if(this->doctors.find(doc) == this->doctors.end())
    {
        std::cout << "This doctor is not part of ehr\n"; //TO be changed 
        return;
    }

    MedicalEncounter newMed;
    p.addMedicalEncounter(newMed);
    
    auto[iter, inserted] = this->patients.insert(p);    
    
    if(!inserted)
    {
        this->patients.insert(p);
        this->patients.erase(iter);
    }
}

void EHR::MainSystem::addDoctor(const Doctor &doc) noexcept
{
    this->doctors.insert(doc);
}

void EHR::MainSystem::healthServiciesPerformed(Patient &patien, const HealthServicies &healthServicies)
{
    const std::string desc = healthServicies.getDescritpion();

    switch (healthServicies.getType())
    {
    case EHR::HealthServiceType::Measuraments :
        patien.addMeasurament(desc);
        break;
    case EHR::HealthServiceType::Refferal :
        // patien.addDoctor(Doctor{desc}, healthServicies.getEncounter());
        break;
    case EHR::HealthServiceType::Prescription :
        patien.addPrescription(desc);
        break;
    
    default:
        std::cerr << "Unreachable!!\n";
        exit(EXIT_FAILURE);
    }
}

void EHR::MainSystem::print() const noexcept
{
    std::cout << "All doctors are: \n";
    for(const auto &d : this->doctors)
    {
        std::cout << d.getName() << ' ';
    }

    std::cout << "\n------------------------------\n";

    std::cout << "All patients are: \n";
    for(const auto &p : this->patients)
    {
        p.print();
    }
    
}
