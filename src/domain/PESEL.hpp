#pragma once
#include <string>
#include <stdexcept>

class PESEL {
    public:
        explicit PESEL(const std::string& value);
        const std::string& value() const;

        bool operator<(const PESEL& pesel) const;
        bool operator>(const PESEL& pesel) const;
        bool operator==(const PESEL& pesel) const;

        static bool isValid(const std::string& value);
    private:
        const std::string value_;
};

std::ostream& operator<<(std::ostream& os, const PESEL& pesel);