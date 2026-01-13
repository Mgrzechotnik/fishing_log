#pragma once

#include <fstream>
#include <cctype>
#include <iostream>
#include "json.hpp"
namespace hk{
    /**
     * @brief Check if the fish species provided by the user is in the fish list
     * 
     * Function accepts the name with mixed case, upper and lower letters
     * and coverts it to lowercase before checking in database
     * 
     * @param name The species of the fish to check
     * @return true if the fish is on the list, false otherwise
     */

    bool checkName(const std::string &name) {
        std::ifstream jsonInput("./fish_list/fishList.json");
        if (!jsonInput.is_open()) {
            std::cerr << "Error: Could not open fishList.json" << std::endl;
            return false;
        }

        nlohmann::json jsonData = nlohmann::json::parse(jsonInput);

        std::string sname = name;

        std::transform(sname.begin(), sname.end(), sname.begin(), ::tolower);

        for (const auto &[category, fishList]: jsonData.items()) {
            for (const auto &fish: fishList) {
                if (fish.get<std::string>() == sname) {
                    return true;
                }
            }
        }

        return false;
    }
}



