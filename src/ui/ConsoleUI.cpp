#include "ConsoleUI.hpp"
#include <iostream>
#include <limits>

ConsoleUI::ConsoleUI(PersonQueryService& service): service_{service}, running{true}{
    registerCommands();
}

void ConsoleUI::registerCommands(){
    commands_["0"] = [this](){exit(); };
    commands_["1"] = [this](){addStudent(); };
    commands_["2"] = [this](){showDatabase(); };
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
    std::cout << "2. Show database\n";
}


void ConsoleUI::exit(){
    running = false;
}

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
}


void ConsoleUI::addStudent(){

    std::string name;
    std::string surname;
    std::string pesel;
    std::string index;
    Gender gender;
    std::string address;

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

void ConsoleUI::showDatabase(){
    ConsoleView view;
    view.printPersons(service_.getAll());
}
