#pragma once

#include <string>
#include <memory>
#include <vector>

class Person;

class PersonCsvFormatter {
public:
    static std::string serialize(const Person& person);
    static std::vector<std::string> deserialize(std::string& line);
};