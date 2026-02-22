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
            auto p1 = std::make_unique<Person>("Adam", "Smith", "98031715344");
            auto p2 = std::make_unique<Person>("Ralf", "Smith", "78032715494");
            auto p3 = std::make_unique<Person>("Ralf", "Smith", "88032715314");
            
            repo.add(std::move(p1));
            repo.add(std::move(p2));
            repo.add(std::move(p3));

            service = std::make_unique<PersonQueryService>(repo);
        }
    };
    
TEST_F(PersonQueryServiceTest, CanSortAscendingByPESEL){
    auto result = service->sortByPESEL(SortOrder::Asc);
    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0]->PESEL(), "78032715494");
    EXPECT_EQ(result[1]->PESEL(), "88032715314");
    EXPECT_EQ(result[2]->PESEL(), "98031715344");
}

TEST_F(PersonQueryServiceTest, CanSortDescendingByPESEL){
    auto result = service->sortByPESEL(SortOrder::Desc);
    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0]->PESEL(), "98031715344");
    EXPECT_EQ(result[1]->PESEL(), "88032715314");
    EXPECT_EQ(result[2]->PESEL(), "78032715494");
}