#include <iostream>
#include "ConsoleView.hpp"
#include "PersonFormatter.hpp"

void ConsoleView::printPersons(const std::vector<const Person*>& persons) const {
    PersonFormatter formatter;
    for(const auto& person: persons){
        std::cout << formatter.format(*person) << '\n';
    }
}