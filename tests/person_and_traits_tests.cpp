#include <gtest/gtest.h>
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include <memory>

TEST(PersonTest, StoresBasicData)
{
    Person person{"Tom", "97121004855"};
    EXPECT_EQ(person.name(), "Tom");
    EXPECT_EQ(person.PESEL(), "97121004855");
}

TEST(PersonTest, addRoleIncreasesRoleCount_sanity)
{
    Person person{"Tom", "97121004855"};
    person.addRole(std::make_shared<StudentRole>("182696"));
    EXPECT_EQ(person.getRole().size(), 1);
}

TEST(PersonTest, getStudentTraitReturnsStudentRole)
{
    Person person{"Tom", "97121004855"};
    person.addRole(std::make_shared<StudentRole>("182696"));

    auto Role = person.getTrait<StudentRole>();
    ASSERT_NE(Role, nullptr);
    EXPECT_EQ(Role->indexNumber(), "182696");
}

TEST(PersonTest, getEmployeeTraitReturnsEmployeeRole)
{
    Person person{"Tom", "97121004855"};
    person.addRole(std::make_shared<EmployeeRole>(19000));

    auto Role = person.getTrait<EmployeeRole>();
    ASSERT_NE(Role, nullptr);
    EXPECT_EQ(Role->salary(), 19000);
}

TEST(PersonTest, GetTraitReturnsNullptrWhenMissing) 
{
    Person p{"Tom", "90031204388"};
    auto indexNumber = p.getTrait<HasIndexNumber>();
    EXPECT_EQ(indexNumber, nullptr);
}


