#include <gtest/gtest.h>
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include "repository/infrastructure/InMemoryPersonRepository.hpp"
#include "services/PersonQueryService.hpp"

#include <memory>


class PersonQueryServiceTest: public ::testing::Test{
    protected:
        InMemoryPersonRepository repo; 
        std::unique_ptr<PersonQueryService> service;

        void SetUp() override{
            auto p1 = std::make_unique<Person>("Adam", "Smith", PESEL("98031715344"));
            auto p2 = std::make_unique<Person>("Ralf", "Adams", PESEL("78032715494"));
            auto p3 = std::make_unique<Person>("John", "Bacon", PESEL("88032715314"));
            p1->addRole(std::make_unique<EmployeeRole>(37000));
            p3->addRole(std::make_unique<EmployeeRole>(70000));
            p1->addRole(std::make_unique<StudentRole>("182696"));
            p3->addRole(std::make_unique<StudentRole>("201332"));
            repo.add(std::move(p1));
            repo.add(std::move(p2));
            repo.add(std::move(p3));

            service = std::make_unique<PersonQueryService>(repo);
        }
    };
    
TEST_F(PersonQueryServiceTest, CanSortAscendingByPESEL){
    auto result = service->sortByPESEL(SortOrder::Asc);
    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0]->pesel(), PESEL("78032715494"));
    EXPECT_EQ(result[1]->pesel(), PESEL("88032715314"));
    EXPECT_EQ(result[2]->pesel(), PESEL("98031715344"));
}

TEST_F(PersonQueryServiceTest, CanSortDescendingByPESEL){
    auto result = service->sortByPESEL(SortOrder::Desc);
    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0]->pesel(), PESEL("98031715344"));
    EXPECT_EQ(result[1]->pesel(), PESEL("88032715314"));
    EXPECT_EQ(result[2]->pesel(), PESEL("78032715494"));
}

TEST_F(PersonQueryServiceTest, CanSortAscendingByLastName){
    auto result = service->sortByName(SortOrder::Asc);
    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0]->surname(), "Adams");
    EXPECT_EQ(result[1]->surname(), "Bacon");
    EXPECT_EQ(result[2]->surname(), "Smith");
}

TEST_F(PersonQueryServiceTest, CanSortDescendingByLastName){
    auto result = service->sortByName(SortOrder::Desc);
    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0]->surname(), "Smith");
    EXPECT_EQ(result[1]->surname(), "Bacon");
    EXPECT_EQ(result[2]->surname(), "Adams");
}

TEST_F(PersonQueryServiceTest, CanSortAscendingBySalary){
    auto result = service->sortBySalary(SortOrder::Asc);
    ASSERT_EQ(result.size(), 3);

    ASSERT_TRUE(result[0]->salary().has_value());
    ASSERT_TRUE(result[1]->salary().has_value());
    ASSERT_FALSE(result[2]->salary().has_value());

    EXPECT_DOUBLE_EQ(result[0]->salary().value(), 37000.0);
    EXPECT_DOUBLE_EQ(result[1]->salary().value(), 70000.0);

}

TEST_F(PersonQueryServiceTest, CanSortDescendingBySalary){
    auto result = service->sortBySalary(SortOrder::Desc);
    ASSERT_EQ(result.size(), 3);

    ASSERT_TRUE(result[0]->salary().has_value());
    ASSERT_TRUE(result[1]->salary().has_value());
    ASSERT_FALSE(result[2]->salary().has_value());

    EXPECT_DOUBLE_EQ(result[0]->salary().value(), 70000.0);
    EXPECT_DOUBLE_EQ(result[1]->salary().value(), 37000.0);
}

TEST_F(PersonQueryServiceTest, CanSortAscendingByIndexNumber){
    auto result = service->sortByIndex(SortOrder::Asc);
    ASSERT_EQ(result.size(), 3);

    ASSERT_TRUE(result[0]->index().has_value());
    ASSERT_TRUE(result[1]->index().has_value());
    ASSERT_FALSE(result[2]->index().has_value());

    EXPECT_EQ(result[0]->index().value(), "182696");
    EXPECT_EQ(result[1]->index().value(), "201332");

}

TEST_F(PersonQueryServiceTest, CanSortDescendingByIndexNumber){
    auto result = service->sortByIndex(SortOrder::Desc);
    ASSERT_EQ(result.size(), 3);

    ASSERT_TRUE(result[0]->index().has_value());
    ASSERT_TRUE(result[1]->index().has_value());
    ASSERT_FALSE(result[2]->index().has_value());

    EXPECT_EQ(result[0]->index().value(), "201332");
    EXPECT_EQ(result[1]->index().value(), "182696");
}

TEST_F(PersonQueryServiceTest, AddStudent_AddsPersonWithStudentRole)
{
    PESEL pesel("44032715314");

    service->addStudent(
        "Jan",
        "Kowalski",
        pesel,
        Gender::Male,
        "Warszawa",
        "123456"
    );

    auto* person = repo.findByPESEL(pesel);

    ASSERT_NE(person, nullptr);

    EXPECT_EQ(person->name(), "Jan");
    EXPECT_EQ(person->surname(), "Kowalski");
    EXPECT_EQ(person->gender(), Gender::Male);

    auto* student = person->getTrait<StudentRole>();
    ASSERT_NE(student, nullptr);
    EXPECT_EQ(student->indexNumber(), "123456");
}

TEST_F(PersonQueryServiceTest, AddStudent_ThrowsWhenPersonExists)
{
    PESEL pesel("44032715314");

    service->addStudent(
        "Jan", "Kowalski", pesel,
        Gender::Male, "Warszawa", "123456"
    );

    EXPECT_THROW(
        service->addStudent(
            "Jan", "Kowalski", pesel,
            Gender::Male, "Warszawa", "123456"
        ),
        std::invalid_argument
    );
}

TEST_F(PersonQueryServiceTest, AddStudentRole_AddsRoleWhenPersonExists){
    PESEL pesel("78032715494");

    auto* person = repo.findByPESEL(pesel);
    ASSERT_NE(person, nullptr);
    auto role = person->getTrait<StudentRole>();
    ASSERT_EQ(role, nullptr);

    service->addStudentRole(pesel, "987654");
    role = person->getTrait<StudentRole>();
    ASSERT_NE(role, nullptr);
    EXPECT_EQ(role->indexNumber(), "987654");
}

TEST_F(PersonQueryServiceTest, AddStudentRole_ThrowsWhenPersonNotFound){
    PESEL pesel("78032710000");

    auto* person = repo.findByPESEL(pesel);
    ASSERT_EQ(person, nullptr);

    EXPECT_THROW(service->addStudentRole(pesel, "987654"), std::invalid_argument);
}

TEST_F(PersonQueryServiceTest, AddStudentRole_ThrowsWhenPersonAlreadyStudent){
    PESEL pesel("33032715314");

    service->addStudent("Jan", "Kowalski", pesel, Gender::Male, "Warszawa", "98765");
    auto* person = repo.findByPESEL(pesel);
    auto* role = person->getTrait<StudentRole>();
    ASSERT_NE(role, nullptr);

    EXPECT_THROW(
        service->addStudentRole(pesel, "999999"),
        std::logic_error
    );
}

TEST_F(PersonQueryServiceTest, RemoveStudentRole_RemovesRoleWhenPersonIsStudent){
    PESEL pesel("98031715344");
    auto* person = repo.findByPESEL(pesel);
    ASSERT_NE(person, nullptr);
    auto* role = person->getTrait<StudentRole>();
    ASSERT_NE(role, nullptr);

    service->removeStudentRole(pesel);

    role = person->getTrait<StudentRole>();
    ASSERT_EQ(role, nullptr);

}

TEST_F(PersonQueryServiceTest, RemoveStudentRole_ThrowWhenPersonNotExists){
    PESEL pesel("78032710000");

    auto* person = repo.findByPESEL(pesel);
    ASSERT_EQ(person, nullptr);

    EXPECT_THROW(service->removeStudentRole(pesel), std::invalid_argument);
}

TEST_F(PersonQueryServiceTest, RemoveStudentRole_ThrowWhenPersonIsNotAStudent){
    PESEL pesel("33032715314");

    service->addEmployee("Jan", "Kowalski", pesel, Gender::Male, "Warszawa", 110000);
    auto* person = repo.findByPESEL(pesel);
    auto* role = person->getTrait<StudentRole>();
    ASSERT_EQ(role, nullptr);

    EXPECT_THROW(
        service->removeStudentRole(pesel),
        std::logic_error
    );
}


TEST_F(PersonQueryServiceTest, AddEmployee_AddsPersonWithEmployeeRole)
{
    PESEL pesel("44032715314");

    service->addEmployee(
        "Jan",
        "Kowalski",
        pesel,
        Gender::Male,
        "Warszawa",
        12000.0
    );

    auto* person = repo.findByPESEL(pesel);

    ASSERT_NE(person, nullptr);

    EXPECT_EQ(person->name(), "Jan");
    EXPECT_EQ(person->surname(), "Kowalski");
    EXPECT_EQ(person->gender(), Gender::Male);

    auto* student = person->getTrait<EmployeeRole>();
    ASSERT_NE(student, nullptr);
    EXPECT_DOUBLE_EQ(student->salary(), 12000.0);
}

TEST_F(PersonQueryServiceTest, AddEmployee_ThrowsWhenPersonExists)
{
    PESEL pesel("44032715314");

    service->addEmployee(
        "Jan", "Kowalski", pesel,
        Gender::Male, "Warszawa", 13000.0
    );

    EXPECT_THROW(
        service->addEmployee(
            "Jan", "Kowalski", pesel,
            Gender::Male, "Warszawa", 14000.0
        ),
        std::invalid_argument
    );
}

TEST_F(PersonQueryServiceTest, AddEmployeeRole_AddsRoleWhenPersonIsNotEmployee){
    PESEL pesel("78032715494");

    auto* person = repo.findByPESEL(pesel);
    ASSERT_NE(person, nullptr);
    auto* role = person->getTrait<EmployeeRole>();
    ASSERT_EQ(role, nullptr);

    service->addEmployeeRole(pesel, 34000.0);
    role = person->getTrait<EmployeeRole>();
    ASSERT_NE(role, nullptr);
    EXPECT_DOUBLE_EQ(role->salary(), 34000.0);
}

TEST_F(PersonQueryServiceTest, AddEmployeeRole_ThrowsWhenPersonNotFound){
    PESEL pesel("78032710000");

    auto* person = repo.findByPESEL(pesel);
    ASSERT_EQ(person, nullptr);

    EXPECT_THROW(service->addEmployeeRole(pesel, 1000000.0), std::invalid_argument);
}

TEST_F(PersonQueryServiceTest, AddEmployeeRole_ThrowsWhenPersonAlreadyEmployee){
    PESEL pesel("33032715314");

    service->addEmployee("Jan", "Kowalski", pesel, Gender::Male, "Warszawa", 350000.0);
    auto* person = repo.findByPESEL(pesel);
    auto* role = person->getTrait<EmployeeRole>();
    ASSERT_NE(role, nullptr);

    EXPECT_THROW(
        service->addEmployeeRole(pesel, 22000.0),
        std::logic_error
    );
}
/////


TEST_F(PersonQueryServiceTest, RemoveEmployeeRole_RemovesRoleWhenPersonIsEmployee){
    PESEL pesel("98031715344");
    auto* person = repo.findByPESEL(pesel);
    ASSERT_NE(person, nullptr);
    auto* role = person->getTrait<EmployeeRole>();
    ASSERT_NE(role, nullptr);

    service->removeEmployeeRole(pesel);

    role = person->getTrait<EmployeeRole>();
    ASSERT_EQ(role, nullptr);

}

TEST_F(PersonQueryServiceTest, RemoveEmployeeRole_ThrowWhenPersonNotExists){
    PESEL pesel("78032710000");

    auto* person = repo.findByPESEL(pesel);
    ASSERT_EQ(person, nullptr);

    EXPECT_THROW(service->removeEmployeeRole(pesel), std::invalid_argument);
}

TEST_F(PersonQueryServiceTest, RemoveEmployeeRole_ThrowWhenPersonIsNotEmployee){
    PESEL pesel("33032715314");

    service->addStudent("Jan", "Kowalski", pesel, Gender::Male, "Warszawa", "56789");
    auto* person = repo.findByPESEL(pesel);
    auto* role = person->getTrait<EmployeeRole>();
    ASSERT_EQ(role, nullptr);

    EXPECT_THROW(
        service->removeEmployeeRole(pesel),
        std::logic_error
    );
}