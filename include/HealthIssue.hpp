#pragma once
#include <vector>
#include <string>
#include "Concepts.hpp"

namespace EHR
{
  
    enum class IssueType
    {
        Chronic, Acute
    };
    
    class HealthIssue
    {
    private:
        IssueType issueType;
        std::string name;
        size_t id;
    public:
        HealthIssue() noexcept = default;
        
        template<typename T>
        requires SomeString<T>
        HealthIssue(IssueType type, const T& nName, size_t nId = 0) noexcept
            : issueType(type), name(nName), id(nId)
        {
        }

        const std::string & getName() const noexcept;
        size_t getId() const noexcept;
        
        auto operator<=>(const HealthIssue& other) const
        {
            return this->name <=> other.name;
        }

        bool operator==(const HealthIssue& other) const
        {
            return this->name == other.name;
        }

        ~HealthIssue() = default;
    };   
    
} // namespace EHR
