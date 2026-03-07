#pragma once
#include "../services/PersonQueryService.hpp"
#include <unordered_map>
#include <string>
#include <functional>
#include "ConsoleView.hpp"

class ConsoleUI{
public:
    explicit ConsoleUI(PersonQueryService& services);
    void run();

private:
    PersonQueryService& service_;
    std::unordered_map<std::string, std::function<void()>> commands_;

    void showMenu();
    void registerCommands();
    void exit();
    void addStudent();
    void addEmployee();
    void showDatabase();
    
    bool running;
};