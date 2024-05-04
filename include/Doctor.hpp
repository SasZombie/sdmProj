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
        static inline size_t globalID = 0;
    public:
        template<typename T>
        requires SomeString<T>
        explicit Doctor(const T& nName, size_t nId = 0)
            : name(nName), signature(nId)
        {   
        }

        void setSignature(size_t nSig) noexcept;
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
