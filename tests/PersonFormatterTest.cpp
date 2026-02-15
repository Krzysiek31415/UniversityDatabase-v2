#include <gtest/gtest.h>
#include "domain/Person.hpp"
#include "ui/PersonFormatter.hpp"

TEST(PersonFormatterTest, FormatsPersonWithAddress) {
    Person p{"Jan", "Kowalski", "12345"};
    p.setGender(Gender::Male);
    p.setAddress("Warszawa");

    PersonFormatter formatter;
    auto result = formatter.format(p);

    EXPECT_NE(result.find("Jan Kowalski"), std::string::npos);
    EXPECT_NE(result.find("Warszawa"), std::string::npos);
}