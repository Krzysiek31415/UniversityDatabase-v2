#pragma once
#include<memory>
#include <vector>

class Person;

class IPersonRepository{
public:
    virtual ~IPersonRepository() = default;
    virtual void add(std::shared_ptr<Person> person) = 0;
    virtual std::vector<std::shared_ptr<Person>> getAll() const = 0; 
};