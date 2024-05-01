#pragma once
#include <vector>

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

        

        ~HealthIssue() = default;
    };   
    
} // namespace EHR
