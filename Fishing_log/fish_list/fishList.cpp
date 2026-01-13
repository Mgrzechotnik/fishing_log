#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>

/**
 * Small program to make your own fish list occuring in your country.
 * Reads form file fish_species_list.txt
 * Create .json file with sorted fishes to categories Coarse Fishes or Predator
 * Created to prevent users from editing json files.
 * Everyone can write own .txt file and put it to the fishh_list folder and change Path to read from file
 */


int main() {

    nlohmann::json jsonFish;
    jsonFish["Predator"] = nlohmann::json::array();
    jsonFish["Coarse_Fish"] = nlohmann::json::array();

    std::ifstream file("fish_species_list.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        std::stringstream ss(line);
        std::string name;
        std::string type;

        if (std::getline(ss, name, ',')) {
            std::getline(ss, type);
            if (type == "P") {
                jsonFish["Predator"].push_back(name);
            } else if (type == "C") {
                jsonFish["Coarse_Fish"].push_back(name);
            } else {
                std::cout << "Fish: " << name << " unrecognized type: " << type << std::endl;
                std::cout << "Type must be P for predator, C for Corase_Fish" << std::endl << std::endl;
            }

        }
    }

    std::ofstream jsonOut("./fishList.json");
    jsonOut << std::setw(4) << jsonFish;
    std::cout << "Fishes saved to json file" << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}

