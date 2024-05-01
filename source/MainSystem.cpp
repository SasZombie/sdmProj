#include "../include/MainSystem.hpp"



void EHR::MainSystem::patienVisits(Patient &p, const Doctor &doc) noexcept
{
    if(this->doctors.find(doc) == this->doctors.end())
    {
        std::cout << "This doctor is not part of ehr\n"; //TO be changed 
        return;
    }

    MedicalEncounter newMed{doc};
    p.addMedicalEncounter(newMed);
    
    auto[iter, inserted] = this->patients.insert(p);    
    
    if(!inserted)
    {
        this->patients.insert(p);
        this->patients.erase(iter);
    }
}

bool EHR::MainSystem::checkDoctor(const Doctor &doc) const noexcept
{
    for(const auto &d : this->doctors)
    {
        if(d == doc)
            return true;
    }
    std::cout << "This doctor isnt part of the system\n";
    return false;
}

bool EHR::MainSystem::checkPatient(const Patient &pat) const noexcept
{
    for(const auto &p : this->patients)
    {
        if(p == pat)
            return true;
    }
    std::cout << "This patient isnt part of the system!\n";
    return false;
}

void EHR::MainSystem::addDoctor(const Doctor &doc) noexcept
{
    this->doctors.insert(doc);
}

void EHR::MainSystem::healthServiciesPerformed(Patient &patien, const HealthServicies &healthServicies) noexcept
{
    const std::string desc = healthServicies.getDescritpion();

    switch (healthServicies.getType())
    {
    case EHR::HealthServiceType::Measuraments :
        patien.addMeasurament(desc);
        break;
    case EHR::HealthServiceType::Refferal :
    {
        MedicalEncounter md = healthServicies.getEncounter();
        patien.addDoctor(Doctor{desc}, md);
        break;

    }
    case EHR::HealthServiceType::Prescription :
        patien.addPrescription(desc);
        break;
    
    default:
        std::cerr << "Unreachable!!\n";
        exit(EXIT_FAILURE);
    }
}

void EHR::MainSystem::signEncounter(const Doctor &doc, size_t pass, const MedicalEncounter &enc) noexcept
{
    if(!checkDoctor(doc))
        return;

    if(doc.getID() != pass)
    {
        std::cout << "Incorrect signature\n";
        return;
    }


    for(auto & encounters : this->activeMedicalEncounters)
    {
        if(encounters == enc)
        {
            encounters.setFinished();
        }
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
