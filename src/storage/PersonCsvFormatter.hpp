#pragma once

#include <string>
#include <memory>

class Person;

class PersonCsvFormatter {
public:
    static std::string serialize(const Person& person);
    static Person* deserialize(const std::string& line);
};