#include "Person.hpp"


Person::Person(const std::string& name,const std::string& surname, const std::string& PESEL): 
    name_{std::move(name)}, 
    surname_{std::move(surname)}, 
    PESEL_{std::move(PESEL)}
{}
const std::string& Person::name() const { return name_; }

const std::string& Person::surname() const { return surname_; }

const std::string& Person::PESEL() const { return PESEL_; }

void Person::addRole(std::unique_ptr<IRole> role){
    roles_.push_back(std::move(role));
}
void Person::setAddress(const std::string& address){
    address_ = std::move(address);
}
const std::optional<std::string> Person::address() const {
    return address_;
}

std::vector<IRole*> Person::getRoles() const{
    std::vector<IRole*> result;
    result.reserve(roles_.size());
    for(const auto& r: roles_){
        result.push_back(r.get());
    }
    return result;
}

void Person::setGender(Gender gender){
    gender_ = gender;
}
Gender Person::gender() const{
    return gender_;
}


