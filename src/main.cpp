#include <iostream>
#include <memory>
#include <algorithm>

#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include "repository/infrastructure/InMemoryPersonRepository.hpp"
#include "repository/interfaces/IPersonRepository.hpp"
#include "ui/ConsoleView.hpp"
#include "ui/PersonFormatter.hpp"
#include "ui/ConsoleUI.hpp"
#include "services/PersonQueryService.hpp"



int main(){
    InMemoryPersonRepository repo;
    PersonQueryService service{repo};

    ConsoleUI console{service};

    console.run();

    return 0;
}

