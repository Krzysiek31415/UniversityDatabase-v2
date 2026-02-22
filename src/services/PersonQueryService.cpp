#include "PersonQueryService.hpp"
#include <algorithm>
#include <functional>

#include "../domain/Person.hpp"


PersonQueryService::PersonQueryService(const IPersonRepository& repo)
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
            return lhs->PESEL() < rhs->PESEL();
        });
    }
    return sortBy([](const Person* lhs,  const Person* rhs){
        return lhs->PESEL() > rhs->PESEL();
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

