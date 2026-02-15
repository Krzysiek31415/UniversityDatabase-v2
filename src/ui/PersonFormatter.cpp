#include "PersonFormatter.hpp"
#include "../domain/Person.hpp"

#include <sstream>

std::string genderToString(Gender gender){

    switch(gender){
        case Gender::Male: return "Male";
        case Gender::Female: return "Female";
        case Gender::Unknown: return "Unknown"; 
    }
    return "Unknown";
}

std::string PersonFormatter::format(const Person& person) const{
    std::ostringstream oss;
    oss << person.name() << " " << person.surname();
    oss << " | gender: " << genderToString(person.gender());

    if (person.address()) {
        oss << " | address: " << person.address().value();
    }

    return oss.str();
}

