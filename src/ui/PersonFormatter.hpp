#pragma once
#include <string>
#include "../domain/Person.hpp"

std::string genderToString(Gender gender);

class PersonFormatter{
    
public:
    std::string format(const Person& person) const;
};