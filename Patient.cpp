#include "../include/Patient.hpp"

void EHR::Patient::addMedicalEncounter(const MedicalEncounter &medEnc) noexcept
{
    this->encounters.emplace_back(medEnc);
}

void EHR::Patient::addPrescription(const std::string &prescriotion) noexcept
{
    this->prescriptions.insert(prescriotion);
}
void EHR::Patient::addMeasurament(const std::string &measure) noexcept
{
    this->measuraments.emplace_back(measure);
}
void EHR::Patient::addDoctor(const Doctor &doc, MedicalEncounter &med) noexcept
{
    med.addDoctor(doc);

    for (size_t i = 0; i < this->encounters.size(); ++i)
    {
        if (med == encounters.at(i))
        {
            encounters.at(i) = med;
        }
    }
}
void EHR::Patient::print() const noexcept
{
    std::cout << "All encounters are: \n";
    for(const auto &e : this->encounters)
    {
        e.print();
    }
}