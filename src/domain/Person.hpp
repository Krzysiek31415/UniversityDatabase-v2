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
    void addRole(std::unique_ptr<IRole> role){
        roles_.push_back(std::move(role));
    }
    std::vector<IRole*> getRole() const{
        std::vector<IRole*> result;
        result.reserve(roles_.size());
        for(const auto& r: roles_){
            result.push_back(r.get());
        }
        return result;
    }
    //void removeRole(std::shared_ptr<IRole> role);

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
    std::string PESEL_;
    std::vector<std::unique_ptr<IRole>> roles_;
};