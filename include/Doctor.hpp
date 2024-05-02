#pragma once
#include <string>
#include "Concepts.hpp"

namespace EHR
{


    class Doctor
    {
    private:
        std::string name;
        size_t ID;              //TODO: Just for testing, need a better signing shit
        static inline size_t globalID = 0;    

    public:
        template<typename T>
        requires SomeString<T>
        explicit Doctor(const T& nName)
            : name(nName)
        {   
            ++globalID;
            this->ID = globalID;
        }

        size_t getID() const noexcept;

        const std::string& getName() const noexcept;

        auto operator<=>(const Doctor& other) const
        {
            return this->name <=> other.name;
        }

        bool operator==(const Doctor& other) const
        {
            return this->name == other.name;
        }


        ~Doctor() = default;
    };
        
} // namespace EHR
