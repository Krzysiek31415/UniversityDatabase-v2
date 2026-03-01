#pragma once

#include <vector>
#include <string>
#include <functional>

#include "../repository/interfaces/IPersonRepository.hpp"
#include "../domain/Person.hpp"

#include "../domain/PESEL.hpp"
#include "../domain/IRole.hpp"
#include "../domain/StudentRole.hpp"
#include "../domain/EmployeeRole.hpp"

enum class SortOrder {
    Asc,
    Desc
};

class PersonQueryService{
public:
    explicit PersonQueryService(IPersonRepository& repo);
    std::vector<const Person*> sortByPESEL(SortOrder order) const;
    std::vector<const Person*> sortByName(SortOrder order) const;
    std::vector<const Person*> sortBySalary(SortOrder order) const;
    std::vector<const Person*> sortByIndex(SortOrder order) const;

    void addStudent(
        const std::string& name,
        const std::string& surname,
        const PESEL& pesel,
        Gender gender,
        const std::string& address,
        const std::string& index
    );

private:
    IPersonRepository& repo_;

    std::vector<const Person*> sortBy(
        std::function<bool(const Person*, const Person*)> comparator) const;
};