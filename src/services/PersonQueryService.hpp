#pragma once

#include <vector>
#include <string>
#include <functional>

#include "../repository/interfaces/IPersonRepository.hpp"

class Person;

enum class SortOrder {
    Asc,
    Desc
};

class PersonQueryService{
public:
    explicit PersonQueryService(const IPersonRepository& repo);
    std::vector<const Person*> sortByPESEL(SortOrder order) const;
    std::vector<const Person*> sortByName(SortOrder order) const;
    std::vector<const Person*> sortBySalary(SortOrder order) const;
private:
    const IPersonRepository& repo_;

    std::vector<const Person*> sortBy(
        std::function<bool(const Person*, const Person*)> comparator) const;
};