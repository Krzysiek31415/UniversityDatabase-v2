#pragma once
#include <string>

class IRole
{
    public:
        virtual std::string roleName() const = 0;
        virtual ~IRole() = default;
};


class HasIndexNumber 
{
    public:
        explicit HasIndexNumber(std::string index)
            : indexNumber_(std::move(index)) {}
    
        const std::string& indexNumber() const {
            return indexNumber_;
        }
    
    protected:
        std::string indexNumber_;
};

class HasSalary
{
    public:
        explicit HasSalary(double salary)
            : salary_(salary) {}
    
        double salary() const {
            return salary_;
        }
    
    protected:
        double salary_;
};