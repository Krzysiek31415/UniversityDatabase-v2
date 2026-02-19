#include "PersonQueryService.hpp"
#include <algorithm>


explicit PersonQueryService::PersonQueryService(const IPersonRepository& repo)
: repo_{repo}
{} 

Person* PersonQueryService::findByPESEL(const std::string& pesel) const{
    Person* result;
    result = std::find_if(repo_.begin(), repo.end(), [&pesel](Person* person){
        return pesel == person->PESEL();
    });
}