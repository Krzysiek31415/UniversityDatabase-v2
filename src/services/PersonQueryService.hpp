#pragma once

#include <vector>
#include <string>

class Person;
class IPersonRepository;

class PersonQueryService{
public:
    explicit PersonQueryService(const IPersonRepository& repo);
    Person* findByPESEL(const std::string& pesel) const;

private:
    const IPersonRepository& repo_;
};