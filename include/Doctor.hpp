#pragma once
#include <string>
#include "Concepts.hpp"

namespace EHR
{
    class Doctor
    {
    private:
        std::string name;
        size_t signature;             

    public:
        template<typename T>
        requires SomeString<T>
        explicit Doctor(const T& nName, size_t signature)
            : name(nName), signature(signature)
        {   
        }

        size_t getSignature() const noexcept;

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
