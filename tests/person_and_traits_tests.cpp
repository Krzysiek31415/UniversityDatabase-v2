#include <gtest/gtest.h>
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include <memory>

class PersonTest: public ::testing::Test{
protected:
    Person person{"Tom", "Smith", "97121004855"};
};

TEST_F(PersonTest, StoresBasicData)
{
    EXPECT_EQ(person.name(), "Tom");
    EXPECT_EQ(person.surname(), "Smith");
    EXPECT_EQ(person.PESEL(), "97121004855");
}

TEST_F(PersonTest, addRoleIncreasesRoleCount_sanity)
{
    person.addRole(std::move(std::make_unique<StudentRole>("182696")));
    EXPECT_EQ(person.getRoles().size(), 1);
}

TEST_F(PersonTest, getStudentTraitReturnsStudentRole)
{
    person.addRole(std::make_unique<StudentRole>("182696"));

    auto Role = person.getTrait<StudentRole>();
    ASSERT_NE(Role, nullptr);
    EXPECT_EQ(Role->indexNumber(), "182696");
}

TEST_F(PersonTest, getEmployeeTraitReturnsEmployeeRole)
{
    person.addRole(std::make_unique<EmployeeRole>(19000));

    auto Role = person.getTrait<EmployeeRole>();
    ASSERT_NE(Role, nullptr);
    EXPECT_EQ(Role->salary(), 19000);
}

TEST_F(PersonTest, GetTraitReturnsNullptrWhenMissing) 
{
    auto indexNumber = person.getTrait<HasIndexNumber>();
    EXPECT_EQ(indexNumber, nullptr);
}


TEST_F(PersonTest, RemoveRole)
{
    person.addRole(std::make_unique<StudentRole>("9876"));
    person.addRole(std::make_unique<EmployeeRole>(18000));

    auto roles = person.getRoles();
    ASSERT_EQ(roles.size(), 2);
    EXPECT_EQ(roles[0]->roleName(), "Student");
    EXPECT_EQ(roles[1]->roleName(), "Employee");
    
    person.removeRole<StudentRole>();
    roles = person.getRoles();
    ASSERT_EQ(roles.size(), 1);
    EXPECT_EQ(roles[0]->roleName(), "Employee");
}

TEST_F(PersonTest, HasNoAddressByDefault){
    EXPECT_FALSE(person.address());
}
TEST_F(PersonTest, CanSetAddress){
    person.setAddress("Breda, Ploegstraat 50");
    ASSERT_TRUE(person.address());
    EXPECT_EQ(person.address(), "Breda, Ploegstraat 50");
}

TEST_F(PersonTest, GenderIsUnknownByDefault){
    EXPECT_EQ(person.gender(), Gender::Unknown);
}
TEST_F(PersonTest, CanSetGender){
    person.setGender(Gender::Male);
    EXPECT_EQ(person.gender(), Gender::Male);
}
