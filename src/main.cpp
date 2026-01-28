#include <iostream>
#include "domain/Person.hpp"
#include "domain/Student.hpp"
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
    
    return 0;
}