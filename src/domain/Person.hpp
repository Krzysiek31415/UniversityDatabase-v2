#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "IRole.hpp"
#include <typeinfo>
#include <string>

class Person
{
public:
    Person(const std::string& name, const std::string& PESEL): name_{std::move(name)}, PESEL_{std::move(PESEL)}
    {}
    const std::string& name() const { return name_; }
    const std::string& PESEL() const { return PESEL_; }
    void addRole(std::unique_ptr<IRole> role){
        roles_.push_back(std::move(role));
    }
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

    std::vector<IRole*> getRoles() const{
        std::vector<IRole*> result;
        result.reserve(roles_.size());
        for(const auto& r: roles_){
            result.push_back(r.get());
        }
        return result;
    }

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
    //std::string surname_;
    //std::string address_;
    std::string PESEL_; 
    std::vector<std::unique_ptr<IRole>> roles_;
};