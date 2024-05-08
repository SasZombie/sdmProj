#include "../include/DataBase.hpp"


EHR::DataBase::DataBase(const std::string& schema) noexcept
{
    con->setSchema(schema);
    con->setAutoCommit(true);
}
//Private Functions
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
            healthIssues.emplace_back(HealthIssue{static_cast<EHR::IssueType>(res->getInt("IssueType")), res->getString("Name"), res->getUInt64("id")});
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

//MARK: Doctors
//---------------------------------------------------------------------------------------------------------------------------
EHR::Doctor EHR::DataBase::createDoctor(const std::string &name) const noexcept
{
    Doctor doc{name};

    this->addDoctor(doc);
    
    return getDoctorByName(name).value();
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

void EHR::DataBase::addDoctorToPatientEncounter(size_t patId, size_t docId, size_t issueId) const noexcept
{
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Patients SET DocID_IssueID = CONCAT(IFNULL(DocID_IssueID, ''), ?) WHERE id = ?");
    const std::string concatenated = std::to_string(docId) + '-' + std::to_string(issueId) + '\n';

    pstmt->setString(1, concatenated);
    pstmt->setUInt64(2, patId);

    pstmt->execute();
    
    delete pstmt;  
}
void EHR::DataBase::addDoctorEncounter(size_t docId, size_t encID) const noexcept
{
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE MedicalEncounters SET DoctorIDs = CONCAT(IFNULL(DoctorIDs, ''), ?) WHERE id = ?");
    const std::string concatenated = std::to_string(docId) + ' ';
    pstmt->setString(1, concatenated);
    pstmt->setUInt64(2, encID);

    pstmt->execute();
    
    delete pstmt;  
}


//MARK: Patients
//----------------------------------------------------------------------------------------------------------------------------------------
const std::set<EHR::Patient> EHR::DataBase::getPatients() const noexcept
{
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Patients");

    std::set<Patient> patients;
    MedicalEncounter med {Doctor{"This Encounter Doesnt Exist!"}};

    while (res->next())
    {

        patients.insert(Patient{res->getString("Name"), res->getUInt64("id"), divByLines(res->getString("Measurements"), '\n'),
                                getAllPrescriptions(res->getString("PrescIDs")), getAllIssues(res->getString("HealthIssuesIDs")),
                                getEncounterById(res->getUInt64("Encounter")).value_or(med)});
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

void EHR::DataBase::uppdatePatient(const std::string &name, size_t medEncId) const noexcept
{
    sql::PreparedStatement *pstmt = con->prepareStatement("UPDATE Patients SET Encounter = ? WHERE Name = ?");
    
    pstmt->setUInt64(1, medEncId);
    pstmt->setString(2, name);

    pstmt->execute();

    delete pstmt;
}
void EHR::DataBase::uppdatePatient(const Patient &pat) const noexcept
{
    this->uppdatePatient(pat.getName(), pat.getMedEnc().getId());
}

//TODO!!!
void EHR::DataBase::uppdatePatientPrescription(const std::vector<size_t> &prescID) const noexcept
{
    for(const auto &num : prescID)
    {
        sql::PreparedStatement *pstmt = con->prepareStatement("UPDATE Prescriptions SET Completed = NOT Completed WHERE id = ?");
    
        pstmt->setUInt64(1, num);

        pstmt->execute();

        delete pstmt;
    }
}

std::optional<EHR::Patient> EHR::DataBase::getPatientByName(const std::string &name) const noexcept
{
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Patients WHERE Name = ?");

    pstmt->setString(1, name);   

    sql::ResultSet* res = pstmt->executeQuery();

    if(res->next())
    {  
        MedicalEncounter med;
        Patient pat{res->getString("Name"), res->getUInt64("id"), divByLines(res->getString("Measurements"), '\n'),
                                getAllPrescriptions(res->getString("PrescIDs")), getAllIssues(res->getString("HealthIssuesIDs")),
                                getEncounterById(res->getUInt64("Encounter")).value_or(med)};

        delete res;
        delete pstmt;
        return pat;
    }

    delete res;
    delete pstmt;

    return std::nullopt;
}

//MARK: Encounters
//--------------------------------------------------------------------------------------------------------------------------------------


EHR::MedicalEncounter EHR::DataBase::createMedEncounter(const Doctor& docr) const noexcept
{

    sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO MedicalEncounters (DoctorIDs) VALUES (?)");
    const std::string concatenated = std::to_string(docr.getSignature()) + ' ';
    pstmt->setString(1, concatenated);

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

const std::vector<EHR::MedicalEncounter> EHR::DataBase::getEncounters() const noexcept
{
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM MedicalEncounters");

    std::vector<MedicalEncounter> encounters;

    while (res->next())
    {

        encounters.emplace_back(MedicalEncounter{this->getAllDoctorsByID(res->getString("DoctorIDs")), this->getAllIssues(res->getString("HealthIssueIDs")), res->getUInt64("id")});
    }

    delete stmt;
    delete res;

    return encounters;
}

std::optional<EHR::MedicalEncounter> EHR::DataBase::getEncounterById(size_t id) const noexcept
{
    std::vector<MedicalEncounter> encounters = getEncounters();
    for(const auto & enc : encounters)
    {
        if(enc.getId() == id)
            return enc;
    }

    return std::nullopt;
}

void EHR::DataBase::signEncounter(size_t docID, size_t encID) const noexcept
{
    sql::PreparedStatement *pstmt = con->prepareStatement("UPDATE MedicalEncounters SET Signature = ? WHERE id = ?");

    pstmt->setUInt64(1, docID);
    pstmt->setUInt64(2, encID);

    pstmt->execute();

    delete pstmt;

}

//id, doctor iDS, HealthIssueIDs, Signature, Prescriptions, Measuraments, 
void EHR::DataBase::archiveEncounter(const std::string &patName) const noexcept
{
    sql::PreparedStatement *pstmt = con->prepareStatement(R"(INSERT INTO ArchiveEncounters (DoctorIDs, PrescIDs, Measurements, PatientID)
                    SELECT DocID_IssueID, PrescIDs, Measurements, id
                    FROM Patients
                    WHERE Name = ?;)");

    pstmt->setString(1, patName);

    pstmt->execute();

    delete pstmt;
}
void EHR::DataBase::deleteEncounter(size_t id) const noexcept
{
   sql::PreparedStatement *pstmt = con->prepareStatement("DELETE FROM ArchiveEncounters WHERE PatientID = ?;");

    pstmt->setUInt64(1, id);

    pstmt->execute();

    delete pstmt;  
}
//MARK: Health Issues
//----------------------------------------------------------------------------------------------------------------------------------------

EHR::HealthIssue EHR::DataBase::createHealthIssue(const std::string &issueName, IssueType iType) const noexcept
{
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM HealthIssues WHERE Name = ? AND IssueType = ?");

    pstmt->setString(1, issueName);
    pstmt->setInt(2, static_cast<int>(iType));

    sql::ResultSet *rs = pstmt->executeQuery();
    size_t id = 0;

    if (rs->next())
    {
        id = rs->getUInt64("id");
        delete rs;
        delete pstmt;

        return {iType, issueName, id};
    } 
    delete pstmt;
    delete rs;


    sql::PreparedStatement *pstmt2 = con->prepareStatement("INSERT INTO HealthIssues (Name, IssueType) VALUES (?, ?)");
    pstmt2->setString(1, issueName);
    pstmt2->setInt(2, static_cast<int>(iType));

    pstmt2->executeUpdate();
    
    delete pstmt2;

    sql::Statement *stmt = con->createStatement();

    sql::ResultSet *rs2 = stmt->executeQuery("SELECT LAST_INSERT_ID()");

    if(rs2->next())
        id = rs2->getUInt64(1);

    delete rs2;
    delete stmt;

    return {iType, issueName, id};
}

void EHR::DataBase::addHealthIssueToPatient(const Patient &pat, const HealthIssue &issue) const noexcept
{
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Patients SET HealthIssuesIDs = CONCAT(IFNULL(HealthIssuesIDs, ''), ?) WHERE id = ?");
    const std::string concatenated = std::to_string(issue.getId()).append(" ");

    pstmt->setString(1, concatenated);
    pstmt->setUInt64(2, pat.getId());

    pstmt->execute();
    
    delete pstmt;   
}
void EHR::DataBase::addHealthIssueToMedicalEncounter(const Patient &pat, const HealthIssue &issue) const noexcept
{
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE MedicalEncounters SET HealthIssueIDs = CONCAT(IFNULL(HealthIssueIDs, ''), ?) WHERE id = ?");
    const std::string concatenated = std::to_string(issue.getId()).append(" ");

    pstmt->setString(1, concatenated);
    pstmt->setUInt64(2, pat.getMedEnc().getId());

    pstmt->execute();
    
    delete pstmt;  
}
//MARK: Prescriptions
//-------------------------------------------------------------------------------------------------------------------------------------------------
size_t EHR::DataBase::createAndGetPrescription(const std::string &str) const noexcept
{
    sql::PreparedStatement *pstmt2 = con->prepareStatement("INSERT INTO Prescriptions (Name, Completed) VALUES (?, FALSE)");
    pstmt2->setString(1, str);

    pstmt2->executeUpdate();
    
    delete pstmt2;

    sql::Statement *stmt = con->createStatement();

    sql::ResultSet *rs2 = stmt->executeQuery("SELECT LAST_INSERT_ID()");
    size_t id = 0;
    if(rs2->next())
        id = rs2->getUInt64(1);

    delete rs2;
    delete stmt;

    return id;
}
void EHR::DataBase::addMeasurement(const Patient &pat, const std::string &str) const noexcept
{
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Patients SET Measurements = CONCAT(IFNULL(Measurements, ''), ?) WHERE id = ?");
    const std::string concatenated = str + '\n';

    pstmt->setString(1, concatenated);
    pstmt->setUInt64(2, pat.getId());

    pstmt->execute();
    
    delete pstmt;  
}


void EHR::DataBase::addPrescription(const Patient &pat, size_t prescID) const noexcept
{
    
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Patients SET PrescIDs = CONCAT(IFNULL(PrescIDs, ''), ?) WHERE id = ?");
    const std::string concatenated = std::to_string(prescID) + ' ';

    pstmt->setString(1, concatenated);
    pstmt->setUInt64(2, pat.getId());

    pstmt->execute();
    
    delete pstmt;  
}


EHR::DataBase::~DataBase()
{
    delete con;
}
