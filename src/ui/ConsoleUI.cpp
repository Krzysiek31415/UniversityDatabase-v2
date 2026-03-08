#include "ConsoleUI.hpp"
#include <iostream>
#include <limits>
#include <utility>

namespace{
    Gender numberToGender(size_t n){
        switch (n)
        {
        case 1:
            return Gender::Male;
        case 2:
            return Gender::Female; 
        default:
            return Gender::Unknown;  
        }
    }

    void readCommonPersonData(std::string &name,
                    std::string &surname,
                    std::string &pesel,
                    Gender &gender,
                    std::string &address){

            std::cout << "Name: ";
            std::cin >> name;

            std::cout << "Surname: ";
            std::cin >> surname;

            std::cout << "PESEL: ";
            std::cin >> pesel;

            std::cout << "Gender:\n";
            std::cout << "1 - male\n2 - female\n3 - unknown\nSelect option:\n";
            size_t n;
            std::cin >> n;
            gender = numberToGender(n);

            std::cout << "Address: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, address);
        }

        std::pair<SortField, SortOrder> numberToEnums(const std::pair<size_t, size_t>& numbers){
            const auto [field, order] = numbers;
            SortField sortField;
            SortOrder sortOrder;

            switch (field){
                case 1: sortField = SortField::INDEX_NUMBER; break;
                case 2: sortField = SortField::PESEL; break;
                case 3: sortField = SortField::SALARY; break;
                case 4: sortField = SortField::SURNAME; break;
                default:
                    std::cout << "Invalid field\n";
                    break;
            }

            switch (order){
                case 1: sortOrder = SortOrder::Asc; break;
                case 2: sortOrder = SortOrder::Desc; break;
                default:
                    std::cout << "Invalid field\n";
                    break;
            }
            return std::pair<SortField, SortOrder>(sortField, sortOrder);
        }
}


ConsoleUI::ConsoleUI(PersonQueryService& service): service_{service}, running{true}{
    registerCommands();
}

void ConsoleUI::registerCommands(){
    commands_["0"] = [this](){exit(); };
    commands_["1"] = [this](){addStudent(); };
    commands_["2"] = [this](){addEmployee(); };
    commands_["3"] = [this](){showDatabase(); };
    commands_["4"] = [this](){runSort(); };
}

void ConsoleUI::run(){
    std::string command;

    while(running){
        showMenu();

        std::cin >> command;

        auto it = commands_.find(command);
        if(it != commands_.end()){
            it->second();
        }else{
            std::cout << "Unknown command\n";
        }
    }
}

void ConsoleUI::showMenu(){
    std::cout << "\n===== MENU =====\n";
    std::cout << "0. Exit\n";
    std::cout << "1. Add student\n";
    std::cout << "2. Add employee\n";
    std::cout << "3. Show database\n";
    std::cout << "4. Sort menu\n";

}

std::pair<size_t, size_t> ConsoleUI::sortMenu(){

    size_t fieldChoice;
    size_t orderChoice;

    std::cout << "Sort by:\n";
    std::cout << "1 - Index number\n";
    std::cout << "2 - PESEL\n";
    std::cout << "3 - Salary\n";
    std::cout << "4 - Surname\n";

    if(!(std::cin >> fieldChoice))
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input\n";
        return {1, 1};
    }

    std::cout << "Order:\n";
    std::cout << "1 - Ascending\n";
    std::cout << "2 - Descending\n";

    if(!(std::cin >> orderChoice))
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input\n";
        return {1, 1};
    }

    return std::pair<size_t, size_t>(fieldChoice, orderChoice);
}

void ConsoleUI::runSort(){

    auto sortChoices = sortMenu();
    auto sortEnums = numberToEnums(sortChoices);
    auto sorted = executeSort(sortEnums.first, sortEnums.second);
    showDatabase(sorted);
}

void ConsoleUI::exit(){
    running = false;
}

void ConsoleUI::addStudent(){

    std::string name;
    std::string surname;
    std::string pesel;
    std::string index;
    Gender gender;
    std::string address;

    readCommonPersonData(name, surname, pesel, gender, address);

    std::cout << "Index: ";
    std::cin >> index;

    service_.addStudent(
        name,
        surname,
        PESEL(pesel),
        gender,
        address,
        index
    );
}

void ConsoleUI::showDatabase() const {
    ConsoleView view;
    std::cout << "\033[32m";
    view.printHeader();
    std::cout << "\033[0m";
    view.printPersons(service_.getAll());
}


void ConsoleUI::showDatabase(const std::vector<const Person*>& persons) const
{
    ConsoleView view;

    std::cout << "\033[32m";
    view.printHeader();
    std::cout << "\033[0m";

    view.printPersons(persons);
}

void ConsoleUI::addEmployee(){

    std::string name;
    std::string surname;
    std::string pesel;
    double salary;
    Gender gender;
    std::string address;

    readCommonPersonData(name, surname, pesel, gender, address);

    std::cout << "Salary: ";
    std::cin >> salary;

    service_.addEmployee(
        name,
        surname,
        PESEL(pesel),
        gender,
        address,
        salary
    );
}

std::vector<const Person*> ConsoleUI::executeSort(SortField field, SortOrder order){
    switch(field){
        case SortField::INDEX_NUMBER: 
            return service_.sortByIndex(order);
        case SortField::PESEL:
            return service_.sortByPESEL(order);
        case SortField::SALARY:
            return service_.sortBySalary(order);
        case SortField::SURNAME:
            return service_.sortByName(order);
        default:
            std::cout << "Invalid sort field\n";
            return {};
    }
} 