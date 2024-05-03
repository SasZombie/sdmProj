#include "../include/DataBase.hpp"

EHR::DataBase::DataBase()
{
    con->setSchema("MainSystem");
}
const std::set<EHR::Doctor> EHR::DataBase::getDoctors() const noexcept
{
    sql::Statement* stmt = con->createStatement();
    sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Doctors");
    
    std::set<Doctor> doctors;
    
    while (res->next()) 
    {
        doctors.insert(Doctor{res->getString("Name"), res->getInt("id")});
    }
    
    delete stmt;
    delete res;

    return doctors;
}

void EHR::DataBase::addDoctor(const Doctor &doc) const noexcept
{
    sql::PreparedStatement * pstmt = con->prepareStatement("INSERT INTO Doctors (Name) VALUES (?)");

    pstmt->setString(1, doc.getName());

    pstmt->execute();

    delete pstmt;
}

std::optional<EHR::Doctor> EHR::DataBase::getDoctorByName(const std::string &name) const noexcept
{
    std::set<Doctor> doctors = this->getDoctors();

    for(const auto & doc : doctors)
    {
        if(doc.getName() == name)
            return doc;
    }

    std::nullopt;
}

const std::set<EHR::Patient> EHR::DataBase::getPatients() const noexcept
{
    sql::Statement* stmt = con->createStatement();
    sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Patients");
    
    std::set<Patient> patients;
    
    while (res->next()) 
    {

        patients.insert(Patient{res->getString("Name"), res->getInt("id"), divByLines(res->getString("Measurements")), 
                getAllPrescriptions(res->getString("PrescIDs")), getAllIssues(res->getString("HealthIssuesIDs")), 
                        getEncounterById(res->getInt("id")).value()});
    }
    
    delete stmt;
    delete res;

    return patients;
}
std::optional<EHR::Patient> EHR::DataBase::getPatientByName(const std::string &name) const noexcept
{
    std::set<Patient> patients = this->getPatients();

    for(const auto & pat : patients)
    {
        if(pat.getName() == name)
            return pat;
    }

    std::nullopt;
}
void EHR::DataBase::uppdatePatientPrescription(const Patient &prep) const noexcept
{
}
void EHR::DataBase::addPatient(const Patient &pat) const noexcept
{
}
EHR::DataBase::~DataBase()
{
    delete con;
}
