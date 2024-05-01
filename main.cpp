#include <iostream>
#include "include/MedicalEncounter.hpp"
#include "include/MainSystem.hpp"
#include "include/HealthServicies.hpp"

int main()
{
    EHR::MainSystem system;

    EHR::Doctor doc("Doctor1");

    EHR::Patient patient{"Patient1"};

    EHR::MedicalEncounter nya{doc};
    EHR::HealthServicies h{EHR::HealthServiceType::Prescription, "Paracetamoul"};

    nya.print();


    system.addDoctor(doc);
    system.patienVisits(patient, doc);
    system.healthServiciesPerformed(patient, h);

    int ok = 0;

    std::cin >> ok;

    if(ok)
    {
        system.deleteMedEnc(nya);
    }
    else
    {
        system.archiveMedEnc(nya);

    }
    system.print();
}