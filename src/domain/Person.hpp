#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <optional>

#include "IRole.hpp"
#include <typeinfo>
#include <string>

class Person
{
public:
    Person(const std::string& name,const std::string& surname, const std::string& PESEL);
    const std::string& name() const;
    const std::string& surname() const; 
    const std::string& PESEL() const;
    void addRole(std::unique_ptr<IRole> role);
    void setAddress(const std::string& address);
    const std::optional<std::string> address() const;

    template<class T>
    void removeRole(){
        roles_.erase(
            std::remove_if(
            roles_.begin(), 
            roles_.end(), 
            [](auto& role){
                return dynamic_cast<T*>(role.get());
            }
            ),
        roles_.end());
    }

    std::vector<IRole*> getRoles() const;

    template<class T>
    T* getTrait() const {
        for(const auto& trait : roles_){
            if(auto result = dynamic_cast<T*>(trait.get())){
                return result;
            }
        }
        return nullptr;
    }

private:
    std::string name_;
    std::string surname_;
    std::optional<std::string> address_;
    std::string PESEL_; 
    std::vector<std::unique_ptr<IRole>> roles_;
};