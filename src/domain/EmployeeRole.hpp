#pragma once
#include "IRole.hpp"

class EmployeeRole: public IRole, public HasSalary
{
    public:
        EmployeeRole(double salary): HasSalary(salary) {}
        std::string roleName() const override {
            return "Employee";
        }
};