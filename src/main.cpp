#include <iostream>
#include "domain/Person.hpp"
#include "domain/Student.hpp"
#include "domain/EmployeeRole.hpp"
#include <memory>


int main(){

    Person p{"Tom", "90031204388"};
    p.addRole(std::make_shared<StudentRole>("182696"));
    std::cout << p.name() << " " << p.PESEL() << std::endl;
    std::cout << p.getRole().front()->roleName() << std::endl;

    for (const auto& role : p.getRole()) {
        if (auto indexed = dynamic_cast<HasIndexNumber*>(role.get())) {
            std::cout << "Index number: " << indexed->indexNumber() << "\n";
        }
    }

    Person d{"Adam", "78041906499"};
    d.addRole(std::make_shared<EmployeeRole>(18000));
    std::cout << d.name() << " " << p.PESEL() << std::endl;
    std::cout << d.getRole().front()->roleName() << std::endl;

    for (const auto& role : d.getRole()) {
        if (auto salary = dynamic_cast<HasSalary*>(role.get())) {
            std::cout << "Salary: " << salary->salary() << "\n";
        }
    }
    
    return 0;
}