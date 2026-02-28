#pragma once
#include<memory>
#include <vector>

class Person;

class IPersonRepository{
public:
    virtual ~IPersonRepository() = default;
    virtual void add(std::unique_ptr<Person> person) = 0;
    virtual void removeByPESEL(const std::string& PESEL) = 0;
    virtual std::vector<const Person*> getAll() const = 0;
    virtual Person* findByPESEL(const std::string& pesel) const = 0;
    virtual std::vector<const Person*> findBySurname(const std::string& surname) const = 0;
};