#include <iostream>

#include "include/UI.hpp"
#include "include/MainSystem.hpp"

constexpr size_t WIDTH = 600, HEIGHT = 800;
constexpr size_t areaWidth = 100, areaHight = 25;


int main()
{
    EHR::MainSystem system{"MainSystem"};
    raylib::Window window(WIDTH, HEIGHT, "Employees");

    std::string stuff = system.viewPatientData("Pacient");
    window.SetPosition(GetMonitorPosition(0));
    SetTargetFPS(60);
    UI::UI ui{WIDTH/2 - areaWidth/2, HEIGHT/2 - areaHight/2, WIDTH, HEIGHT};
    ui.addBox("Add Doctor", 1);
    ui.addBox("PatientVisits", 2);
    ui.addBox("Add Prescription", 2);
    ui.addBox("Add Measuraments", 2);
    ui.addBox("Add Refferal", 3);
    ui.addBox("Add Chronic HI", 3);
    ui.addBox("Add Acute HI", 3);
    
    ui.addBox("Sign Encounter Correct",  2);
    ui.addBox("Sign Encounter Incorrect", 2);

    ui.addBox("Check Patient Data", 2);

    const size_t numberOfBoxes = ui.getBoxes().size();

    while (!window.ShouldClose())
    {
        
        window.BeginDrawing();
        window.ClearBackground(GRAY);
     
        for(size_t i = 0; i < numberOfBoxes; ++i)
        {
            ui.getBoxes()[i].writting();
            ui.getBoxes()[i].draw();

            if(ui.getBoxes()[i].checkButton())
            {
                const UI::TextBoxes box = ui.getBoxes()[i];
                switch (i)
                {
                case 0:
                    system.addDoctor(box.getTexts()[0]);
                    break;
                case 1:
                    system.patienVisits(box.getTexts()[0], box.getTexts()[1]);
                    break;
                case 2:
                    system.healthServiciesPerformed(box.getTexts()[0], EHR::HealthServicies{EHR::HealthServiceType::Prescription, box.getTexts()[1]});
                    break;
                case 3:
                    system.healthServiciesPerformed(box.getTexts()[0], EHR::HealthServicies{EHR::HealthServiceType::Measuraments, box.getTexts()[1]});

                    break;
                case 4:
                    system.healthServiciesPerformed(box.getTexts()[0], EHR::HealthServicies{EHR::HealthServiceType::Refferal, box.getTexts()[1], box.getTexts()[2]});

                    break;
                case 5:
                    system.addHealthIssue(box.getTexts()[0], box.getTexts()[1], box.getTexts()[2], EHR::IssueType::Chronic);

                    break;
                case 6:
                    system.addHealthIssue(box.getTexts()[0], box.getTexts()[1], box.getTexts()[2], EHR::IssueType::Acute);

                    break;
                case 7:
                    system.signEncounterCorrect(std::stoi(box.getTexts()[0]), box.getTexts()[1]);
                    break;
                case 8:
                    system.signEncounterIncorrect(std::stoi(box.getTexts()[0]), box.getTexts()[1]);
                    break;
                case 9:
                    system.viewPatientData(box.getTexts()[0], box.getTexts()[1]);
                    break;
                default:
                    std::cerr << "ERROR, UNREACHEBLE\n";
                    exit(EXIT_FAILURE);
                }

                ui.getBoxes()[i].clear();
            }
        }
        window.EndDrawing();
    }
    
    window.Close();
    raylib::Window seccondWindow(WIDTH, HEIGHT, "Pharmacist");
    SetTargetFPS(60);

    UI::UI ui2{WIDTH/2 - areaWidth/2, HEIGHT/2 - areaHight/2, WIDTH, HEIGHT};

    std::vector<EHR::Prescription> prescriptions;
    std::vector<std::string> strs;
    std::vector<int> completed;
    std::vector<size_t> ids;
  
    ui2.addBox("Name", 1);
    ui2.addCheckBox(strs, completed);

    while (!seccondWindow.ShouldClose())
    {
        
        seccondWindow.BeginDrawing();
        seccondWindow.ClearBackground(GRAY);

     
        ui2.getBoxes()[0].writting();
        ui2.getBoxes()[0].draw();

        if(ui2.getBoxes()[0].checkButton())
        {
            strs.clear();
            completed.clear();
            ids.clear();
            prescriptions = system.printPrescriptions(ui2.getBoxes()[0].getTexts()[0]);
            for(size_t i = 0; i < prescriptions.size(); ++i)
            {
                strs.push_back(prescriptions[i].name);
                if(prescriptions[i].isCompleted)
                {
                    completed.push_back(i);
                }
                ids.push_back(prescriptions[i].id);
            }

            ui2.getBoxes()[0].clear();
            ui2.addCheckBox(strs, completed);
        }
        for(auto &cb : ui2.getCheckBoxes())
        {
            cb.draw();
            if(std::optional<size_t>str = cb.checkButton(); str.has_value())
            {   
                system.changePrescriptionStatus(ids[str.value()]);
            }
        }

        seccondWindow.EndDrawing();
    }
    seccondWindow.Close();

    
}