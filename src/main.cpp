#include <iostream>
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include "repository/infrastructure/InMemoryPersonRepository.hpp"
#include "repository/interfaces/IPersonRepository.hpp"
#include "ui/ConsoleView.hpp"
#include "ui/PersonFormatter.hpp"

#include <memory>

void RepoTest();

int main(){

    Person p{"Tom", "", "90031204388"};
    p.addRole(std::make_unique<StudentRole>("182696"));
    std::cout << p.name() << " " << p.PESEL() << std::endl;
    std::cout << p.getRoles().front()->roleName() << std::endl;

    if(auto role = p.getTrait<StudentRole>()){
        std::cout << role->indexNumber() << std::endl;
    }

    Person d{"Adam", "", "78041906499"};
    d.addRole(std::make_unique<StudentRole>("9876"));
    d.addRole(std::make_unique<EmployeeRole>(18000));
    std::cout << d.name() << " " << d.PESEL() << std::endl;
    std::cout << d.getRoles().front()->roleName() << std::endl;

    if( auto role = d.getTrait<HasSalary>()){
        std::cout << role->salary() << std::endl;
    }
    
    auto roles = d.getRoles();
    for(const auto& r: roles){
        std::cout << r->roleName() << " ";
    }
    std::cout << std::endl;
    d.removeRole<StudentRole>();
    roles = d.getRoles();
    for(const auto& r: roles){
        std::cout << r->roleName() << " ";
    }
    std::cout << std::endl;
    RepoTest();
    return 0;
}

void RepoTest(){
    InMemoryPersonRepository repo;

    auto p1 = std::make_unique<Person>("Dave", "Adams", "95281906877");
    repo.add(std::move(p1));
    auto p2 = std::make_unique<Person>("Hank", "Moon", "123456789");
    p2->addRole(std::make_unique<StudentRole>("211997"));
    repo.add(std::move(p2));
    auto all = repo.getAll();

    for(const auto& elem: all){
        std::cout << elem->name() << std::endl;
        if(auto role = elem->getTrait<StudentRole>()){
            std::cout << role->indexNumber() << std::endl;
        }
    }

    ConsoleView console;
    console.printPersons(repo.getAll());

}