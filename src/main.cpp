#include <iostream>
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include <memory>


int main(){

    Person p{"Tom", "90031204388"};
    p.addRole(std::make_shared<StudentRole>("182696"));
    std::cout << p.name() << " " << p.PESEL() << std::endl;
    std::cout << p.getRole().front()->roleName() << std::endl;

    if(auto role = p.getTrait<StudentRole>()){
        std::cout << role->indexNumber() << std::endl;
    }

    Person d{"Adam", "78041906499"};
    d.addRole(std::make_shared<EmployeeRole>(18000));
    std::cout << d.name() << " " << p.PESEL() << std::endl;
    std::cout << d.getRole().front()->roleName() << std::endl;

    if( auto role = d.getTrait<HasSalary>()){
        std::cout << role->salary() << std::endl;
    }
    
    return 0;
}