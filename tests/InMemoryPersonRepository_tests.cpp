#include <gtest/gtest.h>
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include "repository/infrastructure/InMemoryPersonRepository.hpp"
#include <memory>

TEST(InMemoryPersonRepositoryTest, AddAndGetAllPersons){

    InMemoryPersonRepository repo; 

    auto person1 = std::make_unique<Person>("Adam", "123456789");
    person1->addRole(std::make_unique<StudentRole>("211345"));
    repo.add(std::move(person1));

    auto person2 = std::make_unique<Person>("Ralf", "123456719");
    person2->addRole(std::make_unique<EmployeeRole>(13000));
    repo.add(std::move(person2));

    auto all = repo.getAll();

    ASSERT_EQ(all.size(), 2);
    EXPECT_EQ(all[0]->name(), "Adam");

    auto index = all[0]->getTrait<HasIndexNumber>();
    ASSERT_NE(index, nullptr);
    EXPECT_EQ(index->indexNumber(), "211345");
    
    EXPECT_EQ(all[1]->name(), "Ralf");
}

TEST(InMemoryPersonRepositoryTest, RemovePersonByPESEL){
    InMemoryPersonRepository repo; 
    auto p1 = std::make_unique<Person>("Adam", "12");
    auto p2 = std::make_unique<Person>("Ralf", "45");

    repo.add(std::move(p1));
    repo.add(std::move(p2));

    auto all = repo.getAll();

    ASSERT_EQ(all.size(), 2);
    EXPECT_EQ(all[0]->name(), "Adam");
    EXPECT_EQ(all[1]->name(), "Ralf");

    repo.removeByPESEL("12");
    all = repo.getAll();
    ASSERT_EQ(all.size(), 1);
    EXPECT_EQ(all[0]->name(), "Ralf");
}