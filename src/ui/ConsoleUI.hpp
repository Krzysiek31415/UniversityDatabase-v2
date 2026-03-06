#pragma once
#include "../services/PersonQueryService.hpp"
#include <unordered_map>
#include <string>
#include <functional>

class ConsoleUI{
public:
    explicit ConsoleUI(PersonQueryService& services);
    void run();

private:
    PersonQueryService& services_;
    std::unordered_map<std::string, std::function<void()>> commands_;

    void showMenu();
    void registerCommands();
    void exit();

    bool running;
};