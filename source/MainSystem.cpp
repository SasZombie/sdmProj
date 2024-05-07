#include "../include/MainSystem.hpp"
 
EHR::MainSystem::MainSystem(const std::string &schema)
    : dataBase(schema)
{

}

void EHR::MainSystem::patienVisits(const std::string &pName, const std::string &docName) noexcept
{
    if(!checkDoctor(Doctor{docName}))
    {
        std::cout << "This doctor is not part of our system\n";
        return; 
    }

    Doctor doc = this->dataBase.getDoctorByName(docName).value();


    MedicalEncounter newMed = this->dataBase.createMedEncounter(doc);

    if(!checkPatient(pName))
    {
        this->dataBase.createPatient(pName, newMed.getId());
    }   
    else
    {
        this->dataBase.uppdatePatient(pName, newMed.getId());
        this->dataBase.archiveEncounter(pName);
    }

}
void EHR::MainSystem::addHealthIssue(const std::string &name, const std::string &issueName, const std::string &docName, IssueType iType) const noexcept
{
    std::optional<Patient> p = this->dataBase.getPatientByName(name);

    if(!p.has_value())
    {
        std::cout << "This patient is not in our database! Make sure you call system.patientVisits before\n!";
        return;
    }
    HealthIssue hi = this->dataBase.createHealthIssue(issueName, iType);

    if(p.value().addHealthIssue(hi))
    {
        this->dataBase.addHealthIssueToPatient(p.value(), hi);
    }
    std::optional<Doctor> d = this->dataBase.getDoctorByName(docName);
    if(!d.has_value())
    {
        std::cout << "This doctor is not in our database!\n";
        return;
    }
    this->dataBase.addDoctorToPatientEncounter(p.value().getId(), d.value().getSignature(), hi.getId());
    this->dataBase.addHealthIssueToMedicalEncounter(p.value(), hi);
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
    std::set<Patient> patients2 = dataBase.getPatients();

    if(patients2.find(pat) == patients2.end())
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


void EHR::MainSystem::addDoctor(const Doctor &doc) noexcept
{
    if(checkDoctor(doc))
    {
        std::cout << "Doctor already in the system\n";
        return;
    }

    dataBase.addDoctor(doc);
}

void EHR::MainSystem::addDoctor(const std::string &name) noexcept
{
    if(checkDoctor(Doctor{name}))
    {
        std::cout << "Doctor already in the system\n";
        return;
    }
    dataBase.createDoctor(name);
}

void EHR::MainSystem::healthServiciesPerformed(const std::string &patientName, const HealthServicies &healthServicies) const noexcept
{   

    std::optional<Patient> p = this->dataBase.getPatientByName(patientName);
    if(!p.has_value())
    {
        std::cout << "Cannot apply health Servicies because Patient isnt in our system!\n";
        return;
    }

    const std::string desc = healthServicies.getDescritpion();  

    switch (healthServicies.getType())
    {
    case EHR::HealthServiceType::Measuraments :
        {
            this->dataBase.addMeasurement(p.value(), desc);
            break;
        }
    case EHR::HealthServiceType::Refferal :
    {
        std::optional<Doctor> doc = this->dataBase.getDoctorByName(desc);
        if(doc.has_value())
        {
            this->dataBase.addDoctorToPatientEncounter(p.value().getId(), doc.value().getSignature(), healthServicies.getIssue().getId());
            this->dataBase.addDoctorEncounter(doc.value().getSignature(), p.value().getMedEnc().getId());

        }
        else
            std::cout << "This doctor is not in our dataBase\n";
        break;

    }
    case EHR::HealthServiceType::Prescription :
        {
            size_t id = this->dataBase.createAndGetPrescription(desc);
            this->dataBase.addPrescription(p.value(), id);
            break;
        }   
    default:
        std::cerr << "Unreachable!!\n";
        exit(EXIT_FAILURE);
    }
}

std::optional<EHR::Doctor> EHR::MainSystem::createAndGet(const std::string &name) const noexcept
{   
    if(checkDoctor(Doctor{name}))
    {
        std::cout << "Doctor already in the system\n";
        return std::nullopt;
    }
    return this->dataBase.createDoctor(name);
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


    // for(auto & encounters : this->activeMedicalEncounters)
    // {
    //     if(encounters == enc)
    //     {
    //         encounters.setFinished();
    //     }
    // }

}

void EHR::MainSystem::print() const noexcept
{
    std::set<Doctor> doctors = dataBase.getDoctors();

    std::cout << "All doctors are: \n";
    for(const auto &d : doctors)
    {
        std::cout << d.getName() << ' ' << d.getSignature() << '\n';
    }

    std::cout << "\n------------------------------\n";

    std::set<Patient> patients = dataBase.getPatients();
    std::cout << "All patients are: \n";
    for(const auto &p : patients)
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
void EHR::MainSystem::signEncounterCorrect(size_t digitalSignature, const std::string& patName) const noexcept
{   
    std::optional<Patient> pat = this->dataBase.getPatientByName(patName);
    if(!pat.has_value())
    {
        std::cout << "This Patient is not in our system\n";
        return;
    }
    
    size_t id = pat.value().getId();
    this->dataBase.signEncounter(digitalSignature, id); 
    this->dataBase.deleteEncounter(id); 
}
void EHR::MainSystem::signEncounterIncorrect(size_t digitalSignature, const std::string& patName) const noexcept
{   
    std::optional<Patient> pat = this->dataBase.getPatientByName(patName);
    if(!pat.has_value())
    {
        std::cout << "This Patient is not in our system\n";
        return;
    }
    
    this->dataBase.signEncounter(digitalSignature, pat.value().getMedEnc().getId()); 
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