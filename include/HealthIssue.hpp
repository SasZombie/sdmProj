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

    public:
        HealthIssue() = default;
        
        template<typename T>
        requires SomeString<T>
        HealthIssue(IssueType type, const T& nName)
            : issueType(type), name(nName)
        {
        }

        const std::string & getName() const noexcept;
        
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
