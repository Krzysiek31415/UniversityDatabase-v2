#include <algorithm>
#include <vector>
#include <memory>

#include "../interfaces/IPersonRepository.hpp"
#include "InMemoryPersonRepository.hpp"
#include "../../domain/Person.hpp"



void InMemoryPersonRepository::add(std::unique_ptr<Person> person) {
    persons_.push_back(std::move(person));
}
std::vector<const Person*> InMemoryPersonRepository::getAll() const  {
    std::vector<const Person*> result;
    result.reserve(persons_.size());
    for(const auto& p: persons_){
        result.push_back(p.get());
    }
    return result;
}
void InMemoryPersonRepository::removeByPESEL(const std::string& PESEL) {
    persons_.erase(std::remove_if(
        persons_.begin(), 
        persons_.end(),
        [ &PESEL ](auto& person){
            return person->PESEL() == PESEL;
        }),
        persons_.end()
    );  
}

Person* InMemoryPersonRepository::findByPESEL(const std::string& pesel) const {
    auto result = std::find_if(persons_.begin(), persons_.end(), [&pesel](const auto& person){
        return pesel == person->PESEL();
    });
    if (result == persons_.end()) {
        return nullptr;
    }
    return result->get();
}


