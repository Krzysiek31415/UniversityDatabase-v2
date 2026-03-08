#include "ConsoleUI.hpp"
#include <iostream>
#include <limits>
#include <utility>

namespace{
    Gender numberToGender(size_t n);
    void readCommonPersonData(std::string &name,
        std::string &surname,
        std::string &pesel,
        Gender &gender,
        std::string &address);
    std::pair<SortField, SortOrder> numberToEnums(const std::pair<size_t, size_t>& numbers);
    std::string readLine([[maybe_unused]]const std::string& prompt = {});
    template<class T>
    T readNumber([[maybe_unused]]const std::string& prompt = {} );


    Gender numberToGender(size_t n){
        if(n < 1 || n > 3){
            throw std::runtime_error("Invalid Gender Input");
        }
        return static_cast<Gender>(n);
    }

    void readCommonPersonData(std::string &name,
                    std::string &surname,
                    std::string &pesel,
                    Gender &gender,
                    std::string &address){

            name = readLine("Name: ");
            surname = readLine("Surname: ");
            pesel = readLine("PESEL: ");

            size_t n = readNumber<size_t>("Gender:\n\t1 - male\n\t2 - female\n\t3 - unknown\n\tSelect option:\n");
            gender = numberToGender(n);

            address = readLine("Address: ");
    }

    std::pair<SortField, SortOrder> numberToEnums(const std::pair<size_t, size_t>& numbers){
        const auto [field, order] = numbers;

        if(field < 1 || field > 4){
            throw std::runtime_error("Invalid sort field");
        }
        if(order < 1 || order > 2){
            throw std::runtime_error("Invalid sort order");
        }
        return {
            static_cast<SortField>(field),
            static_cast<SortOrder>(order)
        };
    }

    std::string readLine([[maybe_unused]]const std::string& prompt)
    {
        std::string line;

        while (true) {
            if (!prompt.empty()) {
                std::cout << prompt;
            }

            if (std::getline(std::cin, line)) {
                return line;
            }

            if (std::cin.eof()) {
                throw std::runtime_error("Input stream closed");
            }

            std::cin.clear();
        }
    }

    template<class T>
    T readNumber([[maybe_unused]]const std::string& prompt){

        T value;
        while(true){
            if (!prompt.empty()) {
                std::cout << prompt;
            }

            if(std::cin >> value){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
    
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
            std::cout << "Invalid input. Try again.\n";
        }
    }
}


ConsoleUI::ConsoleUI(PersonQueryService& service): service_{service},storage_{""}, running{true}{
    registerCommands();
}

void ConsoleUI::registerCommands(){
    commands_["0"] = [this](){exit(); };
    commands_["1"] = [this](){addStudent(); };
    commands_["2"] = [this](){addEmployee(); };
    commands_["3"] = [this](){showDatabase(); };
    commands_["4"] = [this](){runSort(); };
    commands_["5"] = [this](){addStudentRole(); };
    commands_["6"] = [this](){removeStudentRole(); };
    commands_["7"] = [this](){addEmployeeRole(); };
    commands_["8"] = [this](){removeEmployeeRole(); };
    commands_["9"] = [this](){saveDatabase();};
}

void ConsoleUI::run(){
    std::string command;

    while(running){
        showMenu();

        if(!(std::cin >> command)){
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        auto it = commands_.find(command);
        if(it != commands_.end()){
            try{
                it->second();
            }
            catch(const std::exception& e){
                std::cout << "Error: " << e.what() << "\n";
            }
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
    std::cout << "5. Add student role\n";
    std::cout << "6. Remove student role\n";
    std::cout << "7. Add employee role\n";
    std::cout << "8. Remove employee role\n";
    std::cout << "9. Save database \n";
}

std::pair<size_t, size_t> ConsoleUI::sortMenu(){

    std::cout << "Sort by:\n";
    std::cout << "1 - Index number\n";
    std::cout << "2 - PESEL\n";
    std::cout << "3 - Salary\n";
    std::cout << "4 - Surname\n";

    size_t fieldChoice = readNumber<size_t>();


    std::cout << "Order:\n";
    std::cout << "1 - Ascending\n";
    std::cout << "2 - Descending\n";

    size_t orderChoice= readNumber<size_t>();

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

    Gender gender;
    std::string address;

    readCommonPersonData(name, surname, pesel, gender, address);

    std::string index = readLine("Index: ");

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
    Gender gender;
    std::string address;

    readCommonPersonData(name, surname, pesel, gender, address);

    double salary = readNumber<double>("Salary: ");

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

void ConsoleUI::addStudentRole(){
    auto pesel = readLine("PESEL: ");
    auto indexNumber = readLine("Index number: ");

    service_.addStudentRole(PESEL{pesel}, indexNumber);
    std::cout << "Student role added\n";
}

void ConsoleUI::removeStudentRole(){
    auto pesel = readLine("PESEL: ");

    service_.removeStudentRole(PESEL{pesel});
    std::cout << "Student role removed\n";
}

void ConsoleUI::addEmployeeRole(){
    auto pesel = readLine("PESEL: ");
    auto salary= readNumber<double>("Salary: ");

    service_.addEmployeeRole(PESEL{pesel}, salary);

    std::cout << "Employee role added\n";
}

void ConsoleUI::removeEmployeeRole(){
    auto pesel = readLine("PESEL: ");

    service_.removeEmployeeRole(PESEL{pesel});

    std::cout << "Employee role removed\n";
}

void ConsoleUI::saveDatabase(){
    storage_.setFileName("../data/persons.csv");
    storage_.save(service_.getAll());
    std::cout << "Database saved\n";
}