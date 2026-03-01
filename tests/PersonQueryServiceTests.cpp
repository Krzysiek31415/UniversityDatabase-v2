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