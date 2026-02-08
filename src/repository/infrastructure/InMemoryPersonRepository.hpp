#pragma once
#include "../interfaces/IPersonRepository.hpp"

class InMemoryPersonRepository: public IPersonRepository{
public: 
    void add(std::shared_ptr<Person> person) override {
        persons_.push_back(std::move(person));
    }
    std::vector<std::shared_ptr<Person>> getAll() const override {
        return persons_;
    }
private:
    std::vector<std::shared_ptr<Person>> persons_;
};
