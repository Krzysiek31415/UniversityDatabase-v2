#include "PersonStorage.hpp"
#include <stdexcept>
#include <fstream>
#include <vector>
#include <iostream>

#include "../domain/Person.hpp"
#include "PersonCsvFormatter.hpp"

PersonStorage::PersonStorage(const std::string& filename)
                : filename_(std::move(filename))
{}

void PersonStorage::save(const std::vector<const Person*>& repo)
{
    std::ofstream file(filename_);

    if (!file){
        throw std::runtime_error("Cannot open file");
    }
    for (const auto* p : repo){
        file << PersonCsvFormatter::serialize(*p) << "\n";
    }
}

void PersonStorage::setFileName(const std::string& name){
    filename_ = std::move(name);
}

