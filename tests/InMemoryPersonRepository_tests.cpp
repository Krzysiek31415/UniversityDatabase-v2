#include <gtest/gtest.h>
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include "repository/infrastructure/InMemoryPersonRepository.hpp"
#include <memory>

TEST(InMemoryPersonRepositoryTest, AddAndGetAllPersons){
    
    InMemoryPersonRepository repo; 

    auto person1 = std::make_shared<Person>("Adam", "123456789");
    person1->addRole(std::make_shared<StudentRole>("211345"));
    repo.add(person1);

    auto person2 = std::make_shared<Person>("Ralf", "123456719");
    person1->addRole(std::make_shared<EmployeeRole>(13000));
    repo.add(person2);

    auto all = repo.getAll();

    ASSERT_EQ(all.size(), 2);
    EXPECT_EQ(all[0]->name(), "Adam");
    EXPECT_EQ(all[0]->getTrait<HasIndexNumber>()->indexNumber(), "211345");
    EXPECT_EQ(all[1]->name(), "Ralf");
}