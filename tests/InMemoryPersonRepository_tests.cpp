#include <gtest/gtest.h>
#include "domain/Person.hpp"
#include "domain/StudentRole.hpp"
#include "domain/EmployeeRole.hpp"
#include "repository/infrastructure/InMemoryPersonRepository.hpp"
#include <memory>
#include <set>

TEST(InMemoryPersonRepositoryTest, AddAndGetAllPersons){

    InMemoryPersonRepository repo; 

    auto person1 = std::make_unique<Person>("Adam", "Smith", PESEL("123456789"));
    person1->addRole(std::make_unique<StudentRole>("211345"));
    repo.add(std::move(person1));

    auto person2 = std::make_unique<Person>("Ralf", "Smith", PESEL("123456719"));
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

class InMemoryPersonRepositoryTestF: public ::testing::Test{
protected:
    InMemoryPersonRepository repo; 
    void SetUp() override{
        auto p1 = std::make_unique<Person>("Adam", "Smithson", PESEL("98031715344"));
        auto p2 = std::make_unique<Person>("Ralf", "Smith", PESEL("88032715314"));
        repo.add(std::move(p1));
        repo.add(std::move(p2));
    }
};

TEST_F(InMemoryPersonRepositoryTestF, RemovePersonByPESEL){
    auto all = repo.getAll();

    ASSERT_EQ(all.size(), 2);
    EXPECT_EQ(all[0]->name(), "Adam");
    EXPECT_EQ(all[1]->name(), "Ralf");

    repo.removeByPESEL(PESEL("98031715344"));
    all = repo.getAll();
    ASSERT_EQ(all.size(), 1);
    EXPECT_EQ(all[0]->name(), "Ralf");
}

TEST_F(InMemoryPersonRepositoryTestF, FindPersonByPESEL){
    auto* person = repo.findByPESEL(PESEL("88032715314"));

    ASSERT_NE(person, nullptr);
    EXPECT_EQ(person->name(), "Ralf");
    EXPECT_EQ(person->pesel(), PESEL("88032715314"));
}

TEST_F(InMemoryPersonRepositoryTestF, CanFindPersonByUniqueSurname){
    auto result = repo.findBySurname("Smith");

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result.front()->surname(), "Smith");
}

TEST_F(InMemoryPersonRepositoryTestF, CanFindSomePeopleBySameSurname){
    auto p = std::make_unique<Person>("Paul", "Smith", PESEL("91032715314"));
    repo.add(std::move(p));

    auto result = repo.findBySurname("Smith");

    ASSERT_EQ(result.size(), 2);

    std::set<PESEL> pesels;
    for(const auto* person : result)
        pesels.insert(person->pesel());

    EXPECT_TRUE(pesels.contains(PESEL("88032715314")));
    EXPECT_TRUE(pesels.contains(PESEL("91032715314")));
}

