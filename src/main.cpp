#include <iostream>
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include "repository/infrastructure/InMemoryPersonRepository.hpp"
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

    InMemoryPersonRepository repo;

    auto p1 = std::make_shared<Person>("Dave", "95281906877");
    repo.add(p1);
    auto p2 = std::make_shared<Person>("Hank", "123456789");
    p2->addRole(std::make_shared<StudentRole>("211997"));
    repo.add(p2);
    auto all = repo.getAll();

    for(const auto& elem: all){
        std::cout << elem->name() << std::endl;
        if(auto role = elem->getTrait<StudentRole>()){
            std::cout << role->indexNumber() << std::endl;
        }
    }

    
    return 0;
}