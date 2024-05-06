#include <iostream>
#include "include/MedicalEncounter.hpp"
#include "include/MainSystem.hpp"
#include "include/HealthServicies.hpp"

int main()
{
    EHR::MainSystem system;
    
    // EHR::Doctor doc("Doctor1");
    // EHR::Doctor doc2("Doctor2");
    // system.createAndGet("Doctor5");
    system.addDoctor("Doctor5");

    system.patienVisits("Patient1", "Doctor5");

    EHR::HealthServicies h{EHR::HealthServiceType::Prescription, "Paracetamol"};
    EHR::HealthServicies prep{EHR::HealthServiceType::Prescription, "Papanas"};
    EHR::HealthServicies measure{EHR::HealthServiceType::Measuraments, "Performed Blood Pressure to be 169"};
    EHR::HealthIssue hi{EHR::IssueType::Chronic, "Cancer"};
    EHR::HealthIssue h2{EHR::IssueType::Chronic, "Black"};

    system.addHealthIssue("Patient1", "Cancer", EHR::IssueType::Chronic);
    system.healthServiciesPerformed("Patient1", measure);

    // system.addDoctor(doc3);
    // system.patienVisits(patient, doc);
    // patient.addHealthIssue(h2);
    // system.healthServiciesPerformed(patient, h);

    system.print();

    // system.viewPatientData(patient, doc);

}