#include "../include/MainSystem.hpp"

 
EHR::MainSystem::MainSystem(const std::string &schema) noexcept
    : dataBase(schema)
{

}

void EHR::MainSystem::patienVisits(const std::string &pName, const std::string &docName) noexcept
{

    std::optional<Doctor> doc = this->dataBase.getDoctorByName(docName);
    if(!doc.has_value())
    {
        std::cout << "This doctor is not part of our system\n";
        return; 
    }
    
    MedicalEncounter newMed = this->dataBase.createMedEncounter(doc.value());
    std::optional<Patient> pat = this->dataBase.getPatientByName(pName);
    if(!pat.has_value())
    {
        this->dataBase.createPatient(pName, newMed.getId());
    }   
    else
    {
        this->dataBase.archiveEncounter(pName);
        this->dataBase.uppdatePatient(pName, newMed.getId());
    }
}
void EHR::MainSystem::addHealthIssue(const std::string &name, const std::string &issueName, const std::string &docName, IssueType iType) const noexcept
{
    std::optional<Patient> p = this->dataBase.getPatientByName(name);

    if(!p.has_value())
    {
        std::cout << "This patient is not in our database! Make sure you call system.patientVisits before!\n";
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
        std::cout << "Cannot apply health Servicies because " + patientName + " isnt in our system!\n";
        return;
    }

    HealthServicies serv{healthServicies.getType(), healthServicies.getDescritpion(),
        this->dataBase.createHealthIssue(healthServicies.getIssue().getName(), healthServicies.getIssue().getType())};

   

    const std::string desc = healthServicies.getDescritpion();  

    switch (serv.getType())
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
            this->dataBase.addDoctorToPatientEncounter(p.value().getId(), doc.value().getSignature(), serv.getIssue().getId());
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

}

void EHR::MainSystem::print() const noexcept
{
    std::set<Doctor> doctors = dataBase.getDoctors();

    std::cout << "All doctors are: \n";
    for(const auto &d : doctors)
    {
        std::cout << d.getName() + ' ' + std::to_string(d.getSignature()) + '\n';
    }

    std::cout << "\n------------------------------\n";

    std::set<Patient> patients = dataBase.getPatients();
    std::cout << "All patients are: \n";
    for(const auto &p : patients)
    {
        p.print();
    }   
}
void EHR::MainSystem::changePrescriptionStatus(size_t presc) noexcept
{
    this->dataBase.uppdatePatientPrescription(presc);
}

std::vector<EHR::Prescription> EHR::MainSystem::printPrescriptions(const std::string &pat) const noexcept
{

    std::optional opt = dataBase.getPatientByName(pat);
    if(!opt.has_value())
    {
        std::cout << "Cannot find patient with name " + pat + '\n';
        return {};
    }

    return opt.value().getPrescriptions();
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


void EHR::MainSystem::viewPatientData(const std::string &patName, const std::string &docName) const noexcept
{
    std::optional<Doctor> doc = this->dataBase.getDoctorByName(docName);
    if(!doc.has_value())
    {
        std::cout << "Doctor not in system\n";
        return;
    }

    std::optional<Patient> pat = this->dataBase.getPatientByName(patName);
    if(!pat.has_value())
    {
        std::cout << "Patient not in system!\n";
        return;
    }

    if(pat.value().getMedEnc().isDoctor(doc.value()))
        pat.value().print();
    else
        std::cout << "You are not allowed to see this patient's data!\n";
}

std::string EHR::MainSystem::viewPatientData(const std::string &patient) const noexcept
{
    std::optional<Patient> pat = this->dataBase.getPatientByName(patient);
    if(!pat.has_value())
    {
        return "Not in system\n";
    }
    return pat.value().print();
}