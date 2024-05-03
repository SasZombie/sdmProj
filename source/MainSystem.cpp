#include "../include/MainSystem.hpp"

void EHR::MainSystem::patienVisits(Patient &p, const Doctor &doc) noexcept
{
    
    if(!checkDoctor(doc))
    {
        std::cout << "This doctor is not part of our system\n";
        return; 
    }
    MedicalEncounter newMed{doc};
    p.addMedicalEncounter(newMed);
    this->activeMedicalEncounters.emplace_back(newMed);
    
    auto[iter, inserted] = this->patients.insert(p);    
    
    if(!inserted)
    {
        this->patients.insert(p);
        this->patients.erase(iter);
    }

 
}

bool EHR::MainSystem::checkDoctor(const Doctor &doc) const noexcept
{
    std::set<Doctor> doctors = dataBase.getDoctors();

    if(doctors.find(doc) == doctors.end())
    {
        return false;
    }

    return true;
}

bool EHR::MainSystem::checkPatient(const Patient &pat) const noexcept
{
    std::set<Patient> patients = dataBase.getPatients();

    if(patients.find(pat) == patients.end())
    {
        return false;
    }

    return true;
}

bool EHR::MainSystem::checkPatient(const std::string &name) const noexcept
{
    if(dataBase.getPatientByName(name).has_value())
        return true;
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
    // this->doctors.insert(doc)
    if(checkDoctor(doc))
    {
        std::cout << "Doctor already in the system\n";
        return;
    }
  
    dataBase.addDoctor(doc);
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
        if(dataBase.getDoctorByName(desc).has_value())
        {
            MedicalEncounter md = healthServicies.getEncounter();
            patien.addDoctor(dataBase.getDoctorByName(desc).value(), md);
        }
        else
            std::cout << "This doctor is not in our dataBase\n";
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

    if(doc.getSignature() != pass)
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
    std::set<Doctor> doctors = dataBase.getDoctors();

    std::cout << "All doctors are: \n";
    for(const auto &d : doctors)
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

void EHR::MainSystem::printPrescriptions(const std::string& pat) noexcept
{

    std::optional opt = dataBase.getPatientByName(pat);
    if(opt.has_value())
    {
        std::cout << "Cannot find patient with ID " << pat << '\n';
        return;
    }

    Patient p = opt.value();

    for(const auto & prep : p.getPrescriptions())
    {
        std::cout << prep.name << ' ' << prep.isCompleted << '\n';
    }

    std::cout << "Please Specify witch prescriptions to complete\n This action CANNOT be undone\n";

    std::vector<std::string> buff;

    //Insert Gui to add to buffer

    for(const std::string & s : buff)
    {
        p.setPrescriptionStatus({true, s});
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

EHR::MainSystem::~MainSystem()
{

}