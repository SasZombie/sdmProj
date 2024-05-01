#include <iostream>
#include "include/MedicalEncounter.hpp"
#include "include/MainSystem.hpp"
#include "include/HealthServicies.hpp"

int main()
{

    EHR::MainSystem system;

    EHR::Doctor doc("SAS");

    EHR::Patient patient{"Zombie"};

    EHR::MedicalEncounter nya{doc};
    EHR::HealthServicies h{EHR::HealthServiceType::Prescription, "Paracetamoul"};



    system.addDoctor(doc);
    system.patienVisits(patient, doc);
    system.healthServiciesPerformed(patient, h);

    system.print();
}