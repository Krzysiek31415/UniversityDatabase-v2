#pragma once
#include <string>
#include <vector>
#include <memory>

#include "IRole.hpp"

class Person
{
public:
    Person(const std::string& name, const std::string& PESEL): name_{std::move(name)}, PESEL_{std::move(PESEL)}
    {}
    const std::string& name() const { return name_; }
    const std::string& PESEL() const { return PESEL_; }
    void addRole(std::shared_ptr<IRole> role){
        roles_.push_back(std::move(role));
    }
    std::vector<std::shared_ptr<IRole>>& getRole(){
        return roles_;
    }
    void removeRole(std::shared_ptr<IRole> role);

    template<class T>
    std::shared_ptr<T> getTrait() const {
        for(const auto& trait : roles_){
            if(auto result = dynamic_pointer_cast<T>(trait)){
                return result;
            }
        }
        return nullptr;
    }

private:
    std::string name_;
    std::string PESEL_;
    std::vector<std::shared_ptr<IRole>> roles_;
};