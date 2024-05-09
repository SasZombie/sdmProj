#include <string>
#include "include/MainSystem.hpp"


int main(int argc, const char **argv)
{
    if(argc < 2)
    {
        std::cout << "Not enough files\n";
        return 0;
    }

    EHR::MainSystem ms{"MainSystem"};

    std::cout << ms.viewPatientData(argv[1]);
}