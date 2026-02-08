#pragma once
#include "../interfaces/IPersonRepository.hpp"

class InMemoryPersonRepository: public IPersonRepository{
public: 
    void add(std::unique_ptr<Person> person) override {
        persons_.push_back(std::move(person));
    }
    std::vector<Person*> getAll() const override {
        std::vector<Person*> result;
        result.reserve(persons_.size());
        for(const auto& p: persons_){
            result.push_back(p.get());
        }
        return result;
    }
private:
    std::vector<std::unique_ptr<Person>> persons_;
};
