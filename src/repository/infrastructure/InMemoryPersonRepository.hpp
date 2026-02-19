#pragma once
#include "../interfaces/IPersonRepository.hpp"
#include <algorithm>


class InMemoryPersonRepository: public IPersonRepository{
public: 
    void add(std::unique_ptr<Person> person) override;
    std::vector<const Person*> getAll() const override;
    void removeByPESEL(const std::string& PESEL) override;
    Person* findByPESEL(const std::string& pesel) const override;
private:
    std::vector<std::unique_ptr<Person>> persons_; 
};
