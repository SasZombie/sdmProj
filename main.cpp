#include <iostream>
#include "include/MedicalEncounter.hpp"
#include "include/MainSystem.hpp"
#include "include/HealthServicies.hpp"

int main()
{
    EHR::MainSystem system;

    // EHR::Doctor doc("Doctor1");
    // EHR::Doctor doc2("Doctor2");
    EHR::Doctor doc3 = system.createAndGet("Doctor5");


    EHR::Patient patient{"Patient1"};

    EHR::HealthServicies h{EHR::HealthServiceType::Prescription, "Paracetamol"};
    EHR::HealthServicies prep{EHR::HealthServiceType::Prescription, "Papanas"};
    EHR::HealthIssue hi{EHR::IssueType::Chronic, "Cancer"};
    EHR::HealthIssue h2{EHR::IssueType::Chronic, "Black"};

    system.addDoctor(doc3);
    // system.patienVisits(patient, doc);
    // patient.addHealthIssue(hi);
    // patient.addHealthIssue(h2);
    // system.healthServiciesPerformed(patient, h);
    std::cout << doc3.getSignature();

    system.print();

    // system.viewPatientData(patient, doc);

}