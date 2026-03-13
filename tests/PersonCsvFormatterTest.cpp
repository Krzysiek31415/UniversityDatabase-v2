#include <gtest/gtest.h>
#include <memory>
#include <iostream>

#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include "repository/infrastructure/InMemoryPersonRepository.hpp"
#include "services/PersonQueryService.hpp"
#include "storage/PersonCsvFormatter.hpp"



TEST(PersonFormaterCsvTest, SerializePersonWithStudentAndEmployeeRoleInString){

    Person person1{"Adam", "Smith", PESEL("98031715344")};
    person1.setAddress("Holtenstraat 7");
    person1.setGender(Gender::Male);
    person1.addRole(std::make_unique<StudentRole>("182699"));
    person1.addRole(std::make_unique<EmployeeRole>(1000));

    auto serializedPerson = PersonCsvFormatter::serialize(person1);
    const std::string line = 
    {"Adam;Smith;98031715344;Male;Holtenstraat 7;182699;1000;"};


    EXPECT_EQ(serializedPerson, line);
}

TEST(PersonFormaterCsvTest, SerializePersonWithStudentRoleInString){

    Person person1{"Adam", "Smith", PESEL("98031715344")};
    person1.setAddress("Holtenstraat 7");
    person1.setGender(Gender::Male);
    person1.addRole(std::make_unique<StudentRole>("182699"));

    auto serializedPerson = PersonCsvFormatter::serialize(person1);
    const std::string line = 
    {"Adam;Smith;98031715344;Male;Holtenstraat 7;182699;;"};

    EXPECT_EQ(serializedPerson, line);
}

TEST(PersonFormaterCsvTest, SerializePersonWithEmployeeRoleInString){

    Person person1{"Adam", "Smith", PESEL("98031715344")};
    person1.setAddress("Holtenstraat 7");
    person1.setGender(Gender::Male);
    person1.addRole(std::make_unique<EmployeeRole>(1000));

    auto serializedPerson = PersonCsvFormatter::serialize(person1);
    const std::string line = 
    {"Adam;Smith;98031715344;Male;Holtenstraat 7;;1000;"};

    EXPECT_EQ(serializedPerson, line);
}

TEST(PersonFormaterCsvTest, SerializePersonInString){

    Person person1{"Adam", "Smith", PESEL("98031715344")};
    person1.setAddress("Holtenstraat 7");
    person1.setGender(Gender::Male);

    auto serializedPerson = PersonCsvFormatter::serialize(person1);
    const std::string line = 
    {"Adam;Smith;98031715344;Male;Holtenstraat 7;;;"};

    EXPECT_EQ(serializedPerson, line);
}

TEST(PersonFormaterCsvTest, SerializePersonWithoutOptionalFieldsInString){

    Person person1{"Adam", "Smith", PESEL("98031715344")};

    auto serializedPerson = PersonCsvFormatter::serialize(person1);
    const std::string line = 
    {"Adam;Smith;98031715344;Unknown;;;;"};

    EXPECT_EQ(serializedPerson, line);
}


TEST(PersonFormaterCsvTest, DeserializePersonLineIntoVector){
    std::string line = 
    "Adam;Smith;98031715344;Male;Holtenstraat 7;182699;1000;";

    std::vector<std::string> expected {
        "Adam",
        "Smith",
        "98031715344",
        "Male",
        "Holtenstraat 7",
        "182699",
        "1000"
    };

    std::vector<std::string> result = PersonCsvFormatter::deserialize(line);
    EXPECT_EQ(result.size(), 7);
    EXPECT_EQ(result, expected);
}

TEST(PersonFormaterCsvTest, DeserializeStudentLineIntoVector){
    std::string line = 
    "Adam;Smith;98031715344;Male;Holtenstraat 7;182699;;";

    std::vector<std::string> expected {
        "Adam",
        "Smith",
        "98031715344",
        "Male",
        "Holtenstraat 7",
        "182699",
        ""
    };

    std::vector<std::string> result = PersonCsvFormatter::deserialize(line);
    EXPECT_EQ(result.size(), 7);
    EXPECT_EQ(result, expected);
}

TEST(PersonFormaterCsvTest, DeserializeEmployeeLineIntoVector){
    std::string line = 
    "Adam;Smith;98031715344;Male;Holtenstraat 7;;1000;";

    std::vector<std::string> expected {
        "Adam",
        "Smith",
        "98031715344",
        "Male",
        "Holtenstraat 7",
        "",
        "1000"
    };

    std::vector<std::string> result = PersonCsvFormatter::deserialize(line);
    EXPECT_EQ(result.size(), 7);
    EXPECT_EQ(result, expected);
}

TEST(PersonFormaterCsvTest, DeserializePersonWithoutOptionalDataLineIntoVector){
    std::string line = 
    "Adam;Smith;98031715344;Unknown;;;;";

    std::vector<std::string> expected {
        "Adam",
        "Smith",
        "98031715344",
        "Unknown",
        "",
        "",
        ""
    };

    std::vector<std::string> result = PersonCsvFormatter::deserialize(line);
    EXPECT_EQ(result.size(), 7);
    EXPECT_EQ(result, expected);
}

TEST(PersonFormaterCsvTest, CreateStudentFromVector){
    std::vector<std::string> fields{
        "Adam",
        "Smith",
        "98031715344",
        "Male",
        "Holtenstraat 7",
        "182699",
        ""
    };
    auto result = PersonCsvFormatter::createPerson(fields);

    EXPECT_EQ(result->name(), "Adam");
    EXPECT_EQ(result->surname(), "Smith");
    EXPECT_EQ(result->pesel(), PESEL{"98031715344"});
    EXPECT_EQ(result->gender(), Gender::Male);
    EXPECT_EQ(result->address(), "Holtenstraat 7");
    EXPECT_EQ(result->index(), "182699");
    EXPECT_EQ(result->getTrait<EmployeeRole>(), nullptr);
}


TEST(PersonFormaterCsvTest, CreateEmployeeFromVector){
    std::vector<std::string> fields{
        "Adam",
        "Smith",
        "98031715344",
        "Male",
        "Holtenstraat 7",
        "",
        "10000"
    };
    auto result = PersonCsvFormatter::createPerson(fields);

    EXPECT_EQ(result->name(), "Adam");
    EXPECT_EQ(result->surname(), "Smith");
    EXPECT_EQ(result->pesel(), PESEL{"98031715344"});
    EXPECT_EQ(result->gender(), Gender::Male);
    EXPECT_EQ(result->address(), "Holtenstraat 7");
    EXPECT_EQ(result->getTrait<StudentRole>(), nullptr);
    EXPECT_EQ(result->salary(), 10000);
}

TEST(PersonFormaterCsvTest, CreatePersonFromVector){
    std::vector<std::string> fields{
        "Adam",
        "Smith",
        "98031715344",
        "Male",
        "Holtenstraat 7",
        "",
        ""
    };
    auto result = PersonCsvFormatter::createPerson(fields);

    EXPECT_EQ(result->name(), "Adam");
    EXPECT_EQ(result->surname(), "Smith");
    EXPECT_EQ(result->pesel(), PESEL{"98031715344"});
    EXPECT_EQ(result->gender(), Gender::Male);
    EXPECT_EQ(result->address(), "Holtenstraat 7");
    EXPECT_EQ(result->getTrait<StudentRole>(), nullptr);
    EXPECT_EQ(result->getTrait<EmployeeRole>(), nullptr);
}


TEST(PersonFormaterCsvTest, ThrowWhenWrongSize){
    std::vector<std::string> fields{
        "Adam",
        "Smith",
        "98031715344",
        
        "Holtenstraat 7",
        "",
        ""
    };
    EXPECT_THROW(PersonCsvFormatter::createPerson(fields), std::logic_error);
}
TEST(PersonFormaterCsvTest, ThrowWhenMissingName){
    std::vector<std::string> fields{
        "",
        "Smith",
        "98031715344",
        "Male",
        "",
        "",
        ""
    };

    EXPECT_THROW(PersonCsvFormatter::createPerson(fields), std::logic_error);
}

TEST(PersonFormaterCsvTest, CreateStudentAndEmployee){
    std::vector<std::string> fields{
        "Adam",
        "Smith",
        "98031715344",
        "Male",
        "Holtenstraat 7",
        "182699",
        "10000"
    };

    auto result = PersonCsvFormatter::createPerson(fields);

    EXPECT_NE(result->getTrait<StudentRole>(), nullptr);
    EXPECT_NE(result->getTrait<EmployeeRole>(), nullptr);
}



