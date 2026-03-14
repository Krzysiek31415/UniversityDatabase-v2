#include <gtest/gtest.h>
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include "repository/infrastructure/InMemoryPersonRepository.hpp"
#include "services/PersonQueryService.hpp"
#include "storage/PersonCsvFormatter.hpp"
#include "storage/PersonStorage.hpp"

#include <memory>
#include <stdexcept>
#include <fstream>

class PersonStorageTest: public testing::Test{
protected:
    InMemoryPersonRepository repo;
    PersonQueryService service{repo};
    PersonStorage storage{};

};

TEST_F(PersonStorageTest, ThrowsWhenFileCannotBeOpened){
    EXPECT_THROW(storage.load(service, "data_test/oneLine.csv"), std::runtime_error);
}

TEST_F(PersonStorageTest, CanLoadOnePerson){
    storage.load(service, "../tests/data_test/oneLine.csv");

    EXPECT_EQ(service.getAll().size(), 1);
    auto person = service.getAll()[0];
    EXPECT_EQ(person->pesel(), PESEL{"98031715344"});
}

TEST_F(PersonStorageTest, CanLoadTwoPersons){
    storage.load(service, "../tests/data_test/twoLines.csv");

    EXPECT_EQ(service.getAll().size(), 2);

    auto person1 = service.getAll()[0];
    auto person2 = service.getAll()[1];

    EXPECT_EQ(person1->pesel(), PESEL{"98031715344"});
    EXPECT_EQ(person2->pesel(), PESEL{"88031715344"});
}

TEST_F(PersonStorageTest, ContinuesWhenEmptyLines){
    storage.load(service, "../tests/data_test/peopleAndEmptyLines.csv");

    EXPECT_EQ(service.getAll().size(), 2);

    auto person1 = service.getAll()[0];
    auto person2 = service.getAll()[1];

    EXPECT_EQ(person1->pesel(), PESEL{"98031715344"});
    EXPECT_EQ(person2->pesel(), PESEL{"88031715344"});
}

TEST_F(PersonStorageTest, SkipsIncorrectLine){
    storage.load(service, "../tests/data_test/invalidLine.csv");

    EXPECT_EQ(service.getAll().size(), 2);

    auto person1 = service.getAll()[0];
    auto person2 = service.getAll()[1];

    EXPECT_EQ(person1->pesel(), PESEL{"98031715344"});
    EXPECT_EQ(person2->pesel(), PESEL{"88031715344"});
}

