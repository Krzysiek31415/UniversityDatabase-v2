#include "ConsoleUI.hpp"
#include <iostream>

ConsoleUI::ConsoleUI(PersonQueryService& services): services_{services}{
    registerCommands();
    running = true;
}

void ConsoleUI::registerCommands(){
    commands_["0"] = [this](){exit(); };
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
}


void ConsoleUI::exit(){
    running = false;
}