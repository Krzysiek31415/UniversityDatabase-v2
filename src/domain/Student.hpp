#pragma once
#include "IRole.hpp"
#include <string>

class StudentRole: public IRole, public HasIndexNumber
{
    public:
        StudentRole(std::string index): HasIndexNumber(std::move(index)) {}
        std::string roleName() const override {
            return "Student";
        }
};