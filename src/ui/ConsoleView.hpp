#pragma once

#include <vector>

#include "../domain/Person.hpp"

class ConsoleView{
public:
    void printPersons(const std::vector<const Person*>& persons) const;
    void printHeader() const;
    void printPerson(const Person& p) const;
};