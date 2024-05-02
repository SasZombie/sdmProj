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
    this->activeMedicalEncounters.emplace_back(newMed);
    
    for(const auto & pat : this->patients)
    {
        if(pat == p)
            return;
    }

    this->patients.emplace_back(p);
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

void EHR::MainSystem::deleteFromActive(const MedicalEncounter &med) noexcept
{
    auto it = std::find(this->activeMedicalEncounters.begin(), this->activeMedicalEncounters.end(), med);
    if (it != this->activeMedicalEncounters.end()) {
        this->activeMedicalEncounters.erase(it);
    }
}
void EHR::MainSystem::addDoctor(const Doctor &doc) noexcept
{
    this->doctors.insert(doc);
}

void EHR::MainSystem::deleteMedEnc(const MedicalEncounter &med, Patient &p) noexcept
{
    this->deleteFromActive(med);
    p.addMedicalEncounter(med);
    
}
void EHR::MainSystem::archiveMedEnc(const MedicalEncounter &med, Patient &p) noexcept
{
    this->deleteFromActive(med);
    this->archivedMedicalEncounters.emplace_back(p.getMedEnc());
    p.addMedicalEncounter(med);
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

    std::cout << "\n------------------------------\n";

    std::cout << "All archived Encounters are: \n";
    for(const auto &p : this->archivedMedicalEncounters)
    {
        p.print();
    }

    std::cout << "\n------------------------------\n";

    std::cout << "All active Encounters are: \n";
    for(const auto &p : this->activeMedicalEncounters)
    {
        p.print();
    }    
}

void EHR::MainSystem::printPrescriptions(const std::string& pat) const noexcept
{
    if(this->checkPatient(pat))
    {
        std::cout << "Cannot find patient with ID " << pat << '\n';
        return;
    }

    for(Patient &p : this->patients)
        if(p == pat)
        {    
            for(const auto & prep : p.getPrescriptions())
            {
                std::cout << prep.name << ' ' << prep.isCompleted << '\n';
            }

            std::cout << "Please Specify witch prescriptions to complete\n This action CANNOT be undone\n";

            std::vector<std::string> buff;

            //Insert Gui to add to buffer

            for(const std::string & s : buff)
            {
                p.setPrescriptionStatus()
            }
        }

}
void EHR::MainSystem::viewPatientData(const Patient &pat, const Doctor &doc) const noexcept
{
    if(pat.getMedEnc().isDoctor(doc))
        pat.print();
    else
        std::cout << "You are not allowed to see this patient's data!\n";
}

void EHR::MainSystem::viewPatientData(const Patient &pat) const noexcept
{
    pat.print();
}