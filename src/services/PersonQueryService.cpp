#include "PersonQueryService.hpp"
#include <algorithm>
#include <functional>
#include <limits>



PersonQueryService::PersonQueryService(IPersonRepository& repo)
: repo_{repo}
{} 

std::vector<const Person*> PersonQueryService::sortBy(
    std::function<bool(const Person*, const Person*)> comparator) const {

    auto result = repo_.getAll();
    std::sort(result.begin(), result.end(), comparator);

    return result;
}

std::vector<const Person*> PersonQueryService::sortByPESEL(SortOrder order) const{
    if(order == SortOrder::Asc){
        return sortBy([](const Person* lhs,  const Person* rhs){
            return lhs->pesel() < rhs->pesel();
        });
    }
    return sortBy([](const Person* lhs,  const Person* rhs){
        return lhs->pesel() > rhs->pesel();
    });
    
}

std::vector<const Person*> PersonQueryService::sortByName(SortOrder order) const{
    if(order == SortOrder::Asc){
        return sortBy([](const Person* lhs,  const Person* rhs){
            return lhs->surname() < rhs->surname();
        });
    }
    return sortBy([](const Person* lhs,  const Person* rhs){
        return lhs->surname() > rhs->surname();
    });  
}

std::vector<const Person*> PersonQueryService::sortBySalary(SortOrder order) const{
    if(order == SortOrder::Asc){
        return sortBy([](const Person* lhs,  const Person* rhs){
            double a = lhs->salary().value_or(std::numeric_limits<double>::max());
            double b = rhs->salary().value_or(std::numeric_limits<double>::max());
            return a < b;
        });
    }
    return sortBy([](const Person* lhs,  const Person* rhs){
            double a = lhs->salary().value_or(std::numeric_limits<double>::lowest());
            double b = rhs->salary().value_or(std::numeric_limits<double>::lowest());
            return a > b;
    }); 
}


std::vector<const Person*> PersonQueryService::sortByIndex(SortOrder order) const{
    if(order == SortOrder::Asc){
        return sortBy([](const Person* lhs,  const Person* rhs){
            const auto& l = lhs->index();
            const auto& r = rhs->index();
            if(!l) return false;
            if(!r) return true;
            return l.value() < r.value();
        });
    }
    return sortBy([](const Person* lhs,  const Person* rhs){
        const auto& l = lhs->index();
        const auto& r = rhs->index();
        if(!l) return false;
        if(!r) return true;
        return l.value() > r.value();
    }); 
}


void PersonQueryService::addStudent(
    const std::string& name,
    const std::string& surname,
    const PESEL& pesel,
    Gender gender,
    const std::string& address,
    const std::string& index)
{
    if (repo_.findByPESEL(pesel))
        throw std::invalid_argument("Person exists");

    auto person = std::make_unique<Person>(name, surname, pesel);

    person->setGender(gender);
    person->setAddress(address);

    person->addRole(std::make_unique<StudentRole>(index));

    repo_.add(std::move(person));
}

