#pragma once

#include <string>
#include "../repository/infrastructure/InMemoryPersonRepository.hpp"

class PersonStorage
{
public:
    PersonStorage(const std::string& filename = 0);
    void save(const std::vector<const Person*>& repo);
    void load();
    void setFileName(const std::string& name);

private:
    std::string filename_;
};