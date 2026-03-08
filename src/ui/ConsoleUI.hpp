#pragma once
#include "../services/PersonQueryService.hpp"
#include <unordered_map>
#include <string>
#include <functional>
#include "ConsoleView.hpp"

enum class SortField{
    PESEL = 1,
    SURNAME,
    SALARY,
    INDEX_NUMBER
};

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
    void showDatabase() const ;
    void showDatabase(const std::vector<const Person*>& persons) const;

    std::vector<const Person*> executeSort(SortField field, SortOrder order);
    std::pair<size_t, size_t> sortMenu();
    void runSort();
    
    bool running;
};