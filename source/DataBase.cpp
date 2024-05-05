#include "../include/DataBase.hpp"

EHR::DataBase::DataBase()
{
    con->setSchema("MainSystem");
    con->setAutoCommit(true);
}

std::vector<EHR::Prescription> EHR::DataBase::getAllPrescriptions(const std::string &prescId) const noexcept
{
    std::vector<std::string> ids = this->divByLines(prescId, ' ');    
    
    std::vector<Prescription> prescriptions;

    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Prescriptions WHERE id = ?");

    for(const auto & num : ids)
    {
        pstmt->setString(1, num);   

        sql::ResultSet* res = pstmt->executeQuery();

        while (res->next())
        {
            prescriptions.emplace_back(Prescription{res->getBoolean("Completed"), res->getString("Name"), res->getUInt64("id")});
        }
        delete res; 
    }
    delete pstmt;

    return prescriptions;
}

std::vector<EHR::HealthIssue> EHR::DataBase::getAllIssues(const std::string &healthId) const noexcept
{
    std::vector<std::string> ids = this->divByLines(healthId, ' ');    
    
    std::vector<HealthIssue> healthIssues;

    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM HealthIssues WHERE id = ?");

    for(const auto & num : ids)
    {
        pstmt->setString(1, num);   

        sql::ResultSet* res = pstmt->executeQuery();

        while (res->next())
        {
            healthIssues.emplace_back(HealthIssue{static_cast<EHR::IssueType>(res->getInt("Completed")), res->getString("Name"), res->getUInt64("id")});
        }
        delete res; 
    }
    delete pstmt;

    return healthIssues;
}

std::set<EHR::Doctor> EHR::DataBase::getAllDoctorsByID(const std::string &doctorIDs) const noexcept
{
    std::vector<std::string> ids = this->divByLines(doctorIDs, ' ');    
    
    std::set<Doctor> doctors;

    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Doctors WHERE id = ?");

    for(const auto & num : ids)
    {
        pstmt->setString(1, num);   

        sql::ResultSet* res = pstmt->executeQuery();

        while (res->next())
        {
            doctors.insert(Doctor{res->getString("Name"), res->getUInt64("id")});
        }
        delete res; 
    }
    delete pstmt;

    return doctors;
}

EHR::Doctor EHR::DataBase::createDoctor(const std::string &name) const noexcept
{
    Doctor doc{name};

    this->addDoctor(doc);
    
    return getDoctorByName(name).value();
}

std::vector<std::string> EHR::DataBase::divByLines(const std::string &str, char delimiter) const noexcept
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
const std::set<EHR::Doctor> EHR::DataBase::getDoctors() const noexcept
{
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Doctors");

    std::set<Doctor> doctors;

    while (res->next())
    {
        doctors.insert(Doctor{res->getString("Name"), res->getUInt64("id")});
    }

    delete stmt;
    delete res;

    return doctors;
}

void EHR::DataBase::addDoctor(const Doctor &doc) const noexcept
{
    sql::PreparedStatement *pstmt = con->prepareStatement("INSERT INTO Doctors (Name) VALUES (?)");

    pstmt->setString(1, doc.getName());

    pstmt->execute();

    delete pstmt;
}

EHR::MedicalEncounter EHR::DataBase::createMedEncounter(const Doctor& docr) const noexcept
{

    sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO MedicalEncounters (DoctorIDs, HealthIssueIDs) VALUES (?, ?)");
    pstmt->setUInt64(1, docr.getSignature());
    pstmt->setUInt64(2, 0);

    pstmt->executeUpdate();
    
    delete pstmt;

    sql::Statement *stmt = con->createStatement();

    sql::ResultSet *rs = stmt->executeQuery("SELECT LAST_INSERT_ID()");
    size_t id = 0;

    if(rs->next())
        id = rs->getUInt64(1);

    delete rs;
    delete stmt;

    return {docr, id};
}

std::optional<EHR::Doctor> EHR::DataBase::getDoctorByName(const std::string &name) const noexcept
{
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Doctors WHERE Name = ?");

    pstmt->setString(1, name);   

    sql::ResultSet* res = pstmt->executeQuery();

    Doctor doc{"Null"};
    if(res->next())
    {  
        doc = Doctor{res->getString("Name"), res->getUInt64("id")};
    }
    else
    {
        delete res; 
        delete pstmt;   

        return std::nullopt;
    }

    delete res;
    delete pstmt;

    return doc;
}

const std::set<EHR::Patient> EHR::DataBase::getPatients() const noexcept
{
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Patients");

    std::set<Patient> patients;

    MedicalEncounter med;

    while (res->next())
    {


        patients.insert(Patient{res->getString("Name"), res->getUInt64("id"), divByLines(res->getString("Measurements"), '\n'),
                                getAllPrescriptions(res->getString("PrescIDs")), getAllIssues(res->getString("HealthIssuesIDs")),
                                getEncounterById(res->getInt("id")).value_or(med)});
    }

    delete stmt;
    delete res;

    return patients;
}
void EHR::DataBase::createPatient(const std::string &name, size_t medEncId) const noexcept
{
    sql::PreparedStatement *pstmt = con->prepareStatement("INSERT INTO Patients (Name, Encounter) VALUES (?, ?)");

    pstmt->setString(1, name);
    pstmt->setUInt64(2, medEncId);

    pstmt->execute();

    delete pstmt;
}

void EHR::DataBase::uppdatePatient(const std::string &name, size_t medEncId) const noexcept
{
    sql::PreparedStatement *pstmt = con->prepareStatement("UPDATE Patients SET Encounter = ? WHERE Name = ?");
    
    pstmt->setUInt64(1, medEncId);
    pstmt->setString(2, name);

    pstmt->execute();

    delete pstmt;
}

std::optional<EHR::Patient> EHR::DataBase::getPatientByName(const std::string &name) const noexcept
{
    std::set<Patient> patients = this->getPatients();

    for (const auto &pat : patients)
    {
        if (pat.getName() == name)
            return pat;
    }

    return std::nullopt;
}
void EHR::DataBase::addEncounter(const MedicalEncounter &med) const noexcept
{
    
}

void EHR::DataBase::uppdateEncounter(const MedicalEncounter &med) const noexcept
{
}

std::optional<EHR::MedicalEncounter> EHR::DataBase::getEncounterById(size_t id) const noexcept
{
    std::set<MedicalEncounter> encounters = getEncounters();

    for(const auto & enc : encounters)
    {
        if(enc.getId() == id)
            return enc;
    }

    return std::nullopt;
}

const std::set<EHR::MedicalEncounter> EHR::DataBase::getEncounters() const noexcept
{
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM MedicalEncounters");

    std::set<MedicalEncounter> encounters;

    while (res->next())
    {

        encounters.insert({this->getAllDoctorsByID(res->getString("DoctorIDs")), this->getAllIssues(res->getString("HealthIssueIDs")), res->getUInt64("id")});
    }

    delete stmt;
    delete res;

    return encounters;
}

void EHR::DataBase::uppdatePatientPrescription(const Patient &prep) const noexcept
{
}

void EHR::DataBase::addPatient(const Patient &pat) const noexcept
{
    sql::PreparedStatement *pstmt = con->prepareStatement("INSERT INTO Patients (Name, Measurements, PrescIDs, HealthIssuesIDs, Encounter) VALUES (?, ?, ?, ?, ?)");

    pstmt->setString(1, pat.getName());
    pstmt->setString(2, pat.getMeasuraments());
    pstmt->setString(3, pat.getPrescriptionIDs());
    pstmt->setString(4, pat.getHealthIssuesIDs());
    pstmt->setUInt64(5, pat.getMedEnc().getId());

    pstmt->execute();

    delete pstmt;
}

void EHR::DataBase::uppdatePatient(const Patient &pat) const noexcept
{
    sql::PreparedStatement *pstmt = con->prepareStatement("UPDATE Patients SET Encounter = ? WHERE id = ?");

    pstmt->setUInt64(1, pat.getMedEnc().getId());
    pstmt->setUInt64(2, pat.getId());

    pstmt->execute();

    delete pstmt;
}

EHR::HealthIssue EHR::DataBase::createHealthIssue(const std::string &issueName, IssueType iType) const noexcept
{
    sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO HealthIssues (Name, IssueType) VALUES (?, ?)");
    pstmt->setString(1, issueName);
    pstmt->setInt(2, static_cast<int>(iType));

    pstmt->executeUpdate();
    
    delete pstmt;

    sql::Statement *stmt = con->createStatement();

    sql::ResultSet *rs = stmt->executeQuery("SELECT LAST_INSERT_ID()");
    size_t id = 0;

    if(rs->next())
        id = rs->getUInt64(1);

    delete rs;
    delete stmt;

    return {iType, issueName, id};
}

EHR::DataBase::~DataBase()
{
    delete con;
}
