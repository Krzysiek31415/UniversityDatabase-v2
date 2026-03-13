#include "PersonCsvFormatter.hpp"
#include "../domain/Person.hpp"
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"

#include <sstream>
#include <optional>
#include <iostream>
#include <type_traits>
#include <memory>
#include <stdexcept>

namespace{
    std::string genderToString(Gender gender){
        switch(gender){
            case Gender::Male: return "Male";
            case Gender::Female: return "Female";
            case Gender::Unknown: return "Unknown"; 
        }
        return "Unknown";
    }

    template<class T>
    std::string optionalToString(const std::optional<T>& data){
        if (!data){
            return ";";
        }
        std::ostringstream oss;
        oss << *data;
        return oss.str() + ";";
    }
}


std::string PersonCsvFormatter::serialize(const Person& person){
    std::stringstream oss;

    oss << person.name() << ';'
        << person.surname() << ';'
        << person.pesel() << ';'
        << genderToString(person.gender()) << ';';

    oss << optionalToString(person.address());
    oss << optionalToString(person.index());
    oss << optionalToString(person.salary());
    return oss.str();
}

std::vector<std::string> PersonCsvFormatter::deserialize(std::string& line){
    std::vector<std::string> data;

    size_t beginData{};
    size_t endData{};

    while(endData != std::string::npos){
        endData = line.find(";", beginData);
        data.push_back(line.substr(beginData, endData-beginData));
        beginData = endData + 1; 
        if(endData == line.size()-1){
            break;
        }
    }
    return data;
}

std::unique_ptr<Person> PersonCsvFormatter::createPerson(const std::vector<std::string>& fields){
    std::unique_ptr<Person> person;
    if(fields.size() == 7 
         && !fields[0].empty() 
         && !fields[1].empty() 
         && !fields[2].empty())
    {
        person = std::make_unique<Person>(fields[0], fields[1], PESEL{fields[2]});
        if(fields[3] == "Male")
        {
            person->setGender(Gender::Male);
        }
        else if(fields[3] == "Female")
        {
            person->setGender(Gender::Female);
        }
        
        if(!fields[4].empty()){
            person->setAddress(fields[4]);
        }
        if(!fields[5].empty()){
            person->addRole(std::make_unique<StudentRole>(fields[5]));
        }
        if(!fields[6].empty()){
            person->addRole(std::make_unique<EmployeeRole>(std::stod(fields[6])));
        }
    }else{
        throw std::logic_error("invalid csv format to cerate Person");
    }
    return person;
}