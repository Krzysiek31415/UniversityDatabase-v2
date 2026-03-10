#include "PersonCsvFormatter.hpp"
#include "../domain/Person.hpp"
#include <sstream>
#include <optional>
#include <iostream>
#include <type_traits>

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