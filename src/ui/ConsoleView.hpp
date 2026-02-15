#pragma once

#include <vector>

class Person;

class ConsoleView{
public:
    void printPersons(const std::vector<const Person*>& persons) const;
};