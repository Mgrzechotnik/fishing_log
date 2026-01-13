#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "json.hpp"

namespace hk {
    /**
     * @brief Static class for managing fish species and types
     * 
     * Class uses a static map to store associations between fish species names
     * and their categories. It loads data from a JSON file and provides a lookup metod
     */
    class FishTypeProvider {
    private:

        /**
         * @brief Map storing fish names as keys and their categories as values
         */
        static inline std::unordered_map<std::string, std::string> m_fishMap;

        /**
         * @brief Flag inicating if the provider has been initialized
         */
        static inline bool m_isInitialized = false;

        /**
         * @brief Deleted constructor to prevent from data leaks
         */

        FishTypeProvider() = delete;

    public:

        /**
         * @brief Initialize the fish data from a JSON file
         * 
         * Open file, parses the fish categories, and populates the internal map.
         * If provider is already initialized, it skips the process.
         * 
         * @param filePath Path to the json file
         * 
         */
        static void initialize(const std::string &filePath) {
            if (m_isInitialized) {
                std::cout << "fishList.json is initialized" << std::endl;
                return;
            }


            std::ifstream jsonInput("./fish_list/fishList.json");

            if (!jsonInput.is_open()) {
                std::cerr << "Error: Could not open fishList.json" << std::endl;
                return;
            }

            nlohmann::json jsonData;
            try {
                jsonInput >> jsonData;
            } catch (const nlohmann::json::parse_error &e) {
                std::cerr << "json parsing error " << std::endl;
                return;
            }

            for (const auto &[category, fishList]: jsonData.items()) {
                for (const auto &fish: fishList) {
                    std::string fishName = fish.get<std::string>();
                    m_fishMap[fishName] = category;
                }
            }

            m_isInitialized = true;
            std::cout << "fish list loaded succesfuly. Total fish: " << m_fishMap.size() << std::endl;
        }

        /**
         * @brief Retrieves the type of a given fish species
         * 
         * @param fishName The name of the fish to check
         * @return The category of the fish
         */

        static std::string getFishType(const std::string &fishName) {
            if (m_fishMap.find(fishName) != m_fishMap.end()) {
                return m_fishMap[fishName];
            }
            return "unknown";
        }
    };
}