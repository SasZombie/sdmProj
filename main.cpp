#include <iostream>
#include "include/MedicalEncounter.hpp"
#include "include/MainSystem.hpp"
#include "include/HealthServicies.hpp"
#include <chrono>

int main()
{
    EHR::MainSystem system{"MainSystem"};
    
    system.addDoctor("Doctor5");

    system.patienVisits("Patient1", "Doctor5");

    EHR::HealthServicies h{EHR::HealthServiceType::Prescription, "Paracetamol"};
    EHR::HealthServicies prep{EHR::HealthServiceType::Prescription, "Papanas"};
    EHR::HealthServicies measure{EHR::HealthServiceType::Measuraments, "Performed Blood Pressure to be 169"};
    EHR::HealthServicies measure2{EHR::HealthServiceType::Measuraments, "Performed Blood Pressure to be BLACK :3"};

    EHR::HealthIssue hi{EHR::IssueType::Chronic, "Cancer"};
    EHR::HealthIssue h2{EHR::IssueType::Chronic, "Black"};

    EHR::HealthServicies refferal{EHR::HealthServiceType::Refferal, "Doctor1", hi};

    system.addHealthIssue("Patient1", "Cancer", "Doctor5", EHR::IssueType::Chronic);
    system.addHealthIssue("Patient1", "Black", "Doctor5", EHR::IssueType::Chronic);
    system.healthServiciesPerformed("Patient1", measure);

    system.healthServiciesPerformed("Patient1", prep);
    system.healthServiciesPerformed("Patient1", refferal);

    system.signEncounterCorrect(15, "Patient1");
    system.print();
    system.printPrescriptions("Patient1");
    system.printPrescriptions("Patient1");

}