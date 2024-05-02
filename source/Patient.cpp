#include "../include/Patient.hpp"

static const std::unordered_map<std::string, std::vector<std::string>> contraIndications = {
    {"Paracetamol", {"Rubeola", "Medicament2", "Medicament3", "Cancer", "Papanas"}}
};

void EHR::Patient::addMedicalEncounter(const MedicalEncounter &medEnc) noexcept
{
    // this->encounters.emplace_back(medEnc);
    this->encounter = medEnc;
}

void EHR::Patient::addPrescription(const std::string &prescriotion) noexcept
{
    if(!contraIndications.contains(prescriotion))
    {
        this->prescriptions.emplace_back(Prescription{false, prescriotion});
        std::cout << "Successfully Added Prescription\n";
        return;
    }
    const std::vector<std::string> notGood = contraIndications.at(prescriotion);

    //Checking if the elem is in noGood
    for (const auto& elem : this->prescriptions)
    {
        if (std::find(notGood.begin(), notGood.end(), elem.name) != notGood.end())
        {
            std::cout << "Cannot add " << prescriotion << " because it is contradicting with " << elem.name << '\n';
            return;
        }
    }
    for (const auto& elem : this->healthIssues)
    {
        if (std::find(notGood.begin(), notGood.end(), elem.getName()) != notGood.end())
        {
            std::cout << "Cannot add " << prescriotion << " because it is contradicting with " << elem.getName() << '\n';
            return;
        }
    }

    this->prescriptions.emplace_back(Prescription{false, prescriotion});
    std::cout << "Successfully Added Prescription\n";
}
void EHR::Patient::addMeasurament(const std::string &measure) noexcept
{
    this->measuraments.emplace_back(measure);
}
void EHR::Patient::addDoctor(const Doctor &doc, MedicalEncounter &med) noexcept
{
    this->encounter.addDoctor(doc);
    // med.addDoctor(doc);

    // for (size_t i = 0; i < this->encounters.size(); ++i)
    // {
    //     if (med == encounters.at(i))
    //     {
    //         encounters.at(i) = med;
    //     }
    // }
}
void EHR::Patient::print() const noexcept
{
    std::cout << this->name << '\n';
    std::cout << "All encounters are: \n";
    this->encounter.print();
    // for(const auto &e : this->encounters)
    // {
    //     e.print();
    // }
}

const EHR::MedicalEncounter &EHR::Patient::getMedEnc() const noexcept
{
    return this->encounter;
}
void EHR::Patient::addHealthIssue(const HealthIssue &issue) noexcept
{
    this->healthIssues.insert(issue);
    this->encounter.addHealthIssue(issue);
}

void EHR::Patient::setPrescriptionStatus(const Prescription &prep) noexcept
{
    for (size_t i = 0; i < prescriptions.size(); ++i)
    {
        if(prescriptions[i].name == prep.name)
        {
            prescriptions[i] = prep;
        }
    }
    
}
const std::vector<EHR::Prescription> &EHR::Patient::getPrescriptions() const noexcept
{
    return this->prescriptions;
}