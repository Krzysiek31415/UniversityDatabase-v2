#pragma once
#include "../interfaces/IPersonRepository.hpp"
#include <algorithm>

class InMemoryPersonRepository: public IPersonRepository{
public: 
    void add(std::unique_ptr<Person> person) override {
        persons_.push_back(std::move(person));
    }
    std::vector<const Person*> getAll() const override {
        std::vector<const Person*> result;
        result.reserve(persons_.size());
        for(const auto& p: persons_){
            result.push_back(p.get());
        }
        return result;
    }
    void removeByPESEL(const std::string& PESEL) override{
        persons_.erase(std::remove_if(
            persons_.begin(), 
            persons_.end(),
            [ &PESEL ](auto& person){
                return person->PESEL() == PESEL;
            }),
            persons_.end()
        );
    }
private:
    std::vector<std::unique_ptr<Person>> persons_;
};
