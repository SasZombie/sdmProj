#include "../include/DoctorDB.hpp"

EHR::DoctorDB::DoctorDB(DataBase &nDb)
    : db(nDb)
{

}

void EHR::DoctorDB::addDoctor(const Doctor &doc) const noexcept
{
    sql::PreparedStatement *pstmt = db.prepareStatement("INSERT INTO Doctors (Name) VALUES (?)");

    pstmt->setString(1, doc.getName());

    pstmt->execute();

    delete pstmt;
}

EHR::Doctor EHR::DoctorDB::createDoctor(const std::string &name) const noexcept
{
    Doctor doc{name};

    this->addDoctor(doc);
    
    return getDoctorByName(name).value();
}


std::optional<EHR::Doctor> EHR::DoctorDB::getDoctorByName(const std::string &name) const noexcept
{
    sql::PreparedStatement* pstmt = db.prepareStatement("SELECT * FROM Doctors WHERE Name = ?");

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

void EHR::DoctorDB::addDoctorToPatientEncounter(size_t patId, size_t docId, size_t issueId) const noexcept
{
    sql::PreparedStatement* pstmt = db.prepareStatement("UPDATE Patients SET DocID_IssueID = CONCAT(IFNULL(DocID_IssueID, ''), ?) WHERE id = ?");
    const std::string concatenated = std::to_string(docId) + '-' + std::to_string(issueId) + '\n';

    pstmt->setString(1, concatenated);
    pstmt->setUInt64(2, patId);

    pstmt->execute();
    
    delete pstmt;  
}

void EHR::DoctorDB::addDoctorEncounter(size_t docId, size_t encID) const noexcept
{
    sql::PreparedStatement* pstmt = db.prepareStatement("UPDATE MedicalEncounters SET DoctorIDs = CONCAT(IFNULL(DoctorIDs, ''), ?) WHERE id = ?");
    const std::string concatenated = std::to_string(docId) + ' ';
    pstmt->setString(1, concatenated);
    pstmt->setUInt64(2, encID);

    pstmt->execute();
    
    delete pstmt;  
}

// void EHR::DoctorDB::addDoctorEncounter(size_t docId, size_t issueId) const noexcept
// {
// }
// void EHR::DoctorDB::addDoctorToPatientEncounter(size_t patId, size_t docId, size_t issueId) const noexcept
// {
// }
// void EHR::DoctorDB::addDoctor(const Doctor &doc) const noexcept
// {
// }
// const std::set<Doctor> EHR::DoctorDB::getDoctors() const noexcept
// {
//     return std::set<Doctor>();
// }
// Doctor EHR::DoctorDB::createDoctor(const std::string &name) const noexcept
// {
//     return Doctor();
// }