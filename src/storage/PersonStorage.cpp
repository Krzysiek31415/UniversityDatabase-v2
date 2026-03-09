#include "PersonStorage.hpp"
#include <stdexcept>
#include <fstream>
#include <vector>
#include <iostream>

#include "../domain/Person.hpp"
#include "PersonCsvFormatter.hpp"


void PersonStorage::save(const std::vector<const Person*>& repo, const std::string& filename)
{

    std::ofstream file(filename);

    if (!file){
        throw std::runtime_error("Cannot open file");
    }
    for (const auto* p : repo){
        file << PersonCsvFormatter::serialize(*p) << "\n";
    }
}

