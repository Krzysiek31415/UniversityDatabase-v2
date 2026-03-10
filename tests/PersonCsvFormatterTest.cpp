#include <gtest/gtest.h>
#include <memory>

#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include "repository/infrastructure/InMemoryPersonRepository.hpp"
#include "services/PersonQueryService.hpp"
#include "storage/PersonCsvFormatter.hpp"



TEST(PersonFormaterCsvTest, serializerCanTransformPersonWithStudentAndEmployeeRoleInString){

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

TEST(PersonFormaterCsvTest, serializerCanTransformPersonWithStudentRoleInString){

    Person person1{"Adam", "Smith", PESEL("98031715344")};
    person1.setAddress("Holtenstraat 7");
    person1.setGender(Gender::Male);
    person1.addRole(std::make_unique<StudentRole>("182699"));

    auto serializedPerson = PersonCsvFormatter::serialize(person1);
    const std::string line = 
    {"Adam;Smith;98031715344;Male;Holtenstraat 7;182699;;"};

    EXPECT_EQ(serializedPerson, line);
}

TEST(PersonFormaterCsvTest, serializerCanTransformPersonWithEmployeeRoleInString){

    Person person1{"Adam", "Smith", PESEL("98031715344")};
    person1.setAddress("Holtenstraat 7");
    person1.setGender(Gender::Male);
    person1.addRole(std::make_unique<EmployeeRole>(1000));

    auto serializedPerson = PersonCsvFormatter::serialize(person1);
    const std::string line = 
    {"Adam;Smith;98031715344;Male;Holtenstraat 7;;1000;"};

    EXPECT_EQ(serializedPerson, line);
}

TEST(PersonFormaterCsvTest, serializerCanTransformPersonInString){

    Person person1{"Adam", "Smith", PESEL("98031715344")};
    person1.setAddress("Holtenstraat 7");
    person1.setGender(Gender::Male);

    auto serializedPerson = PersonCsvFormatter::serialize(person1);
    const std::string line = 
    {"Adam;Smith;98031715344;Male;Holtenstraat 7;;;"};

    EXPECT_EQ(serializedPerson, line);
}

TEST(PersonFormaterCsvTest, serializerCanTransformPersonWithoutOptionalFieldsInString){

    Person person1{"Adam", "Smith", PESEL("98031715344")};

    auto serializedPerson = PersonCsvFormatter::serialize(person1);
    const std::string line = 
    {"Adam;Smith;98031715344;Unknown;;;;"};

    EXPECT_EQ(serializedPerson, line);
}


