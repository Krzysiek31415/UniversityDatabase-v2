#pragma once

#include <string>
#include "../repository/infrastructure/InMemoryPersonRepository.hpp"

class PersonStorage
{
public:
    void save(const std::vector<const Person*>& repo, const std::string& name);
    void load();
};