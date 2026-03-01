#include <string>
#include <stdexcept>
#include "PESEL.hpp"

namespace{
    std::string validateOrThrow(const std::string& value){
        if(!PESEL::isValid(value)){
            throw std::invalid_argument("Invalid PESEL");
        }
        return value;
    }
}

PESEL::PESEL(const std::string& value): value_{validateOrThrow(value)}
{}


const std::string& PESEL::value() const { 
    return value_; 
}

bool PESEL::isValid([[maybe_unused]] const std::string& value){
    return true;
}


std::ostream& operator<<(std::ostream& os, const PESEL& pesel) {
    os << pesel.value();
    return os;
}

bool PESEL::operator<(const PESEL& pesel) const{
    return value_ < pesel.value();
}
        
bool PESEL::operator>(const PESEL& pesel) const{
    return value_ > pesel.value();
}

bool PESEL::operator==(const PESEL& pesel) const{
    return value_ == pesel.value();
}