#pragma once
#include <string>

class Person;

class PersonFormatter{
public:
    std::string format(const Person& person) const;
};