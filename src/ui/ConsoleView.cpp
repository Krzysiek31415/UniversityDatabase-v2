#include <iostream>
#include <iomanip>
#include "ConsoleView.hpp"
#include "PersonFormatter.hpp"

namespace{
    constexpr int NAME_W = 12;
    constexpr int SURNAME_W = 15;
    constexpr int ADDRESS_W = 35;
}

std::string cutStr(const std::string& s, std::size_t width)
{
    if (s.size() <= width)
        return s;

    return s.substr(0, width);
}

void ConsoleView::printPersons(const std::vector<const Person*>& persons) const {
    for(const auto& person: persons){
        printPerson(*person);
    }
}

void ConsoleView::printHeader() const {
    std::cout
        << std::left
        << std::setw(NAME_W) << "Name"
        << std::setw(SURNAME_W) << "Surname"
        << std::setw(15) << "PESEL"
        << std::setw(10) << "Gender"
        << std::setw(ADDRESS_W) << "Address"
        << std::setw(10) << "Index"
        << std::setw(10) << "Salary"
        << '\n';

    std::cout << std::string(45 + NAME_W + SURNAME_W + ADDRESS_W, '-') << '\n';
}

void ConsoleView::printPerson(const Person& p) const {

    std::cout
        << std::left
        << std::setw(NAME_W) << p.name()
        << std::setw(SURNAME_W) << p.surname()
        << std::setw(15) << p.pesel()
        << std::setw(10) << genderToString(p.gender())
        << std::setw(ADDRESS_W) << cutStr((p.address() ? *p.address() : "---"), ADDRESS_W) 
        << std::setw(10) << (p.index() ? *p.index() : "---")
        << std::setw(10) << (p.salary() ? std::to_string(*p.salary()) : "---")
        << '\n';
}