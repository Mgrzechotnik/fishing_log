#pragma once

#include <random>
#include "checkName.hpp"
#include "FishTypeProvider.hpp"

namespace hk {

    /**
     * @brief Base class represents a fish object
     * 
     * Stores base parameters name,length,weight hour and unique id for the fish
     * Serves as a base class for Predator and CoarseFish class
     * 
     */

    class Fish {
    protected:
        std::string m_name;
        std::string m_type;
        double m_weight;
        double m_length;
        int m_hour;
        int m_id;

        /**
         * @brief Generate unique id for fish
         * 
         * @return a randomly generated number between 1 and 99999
         */

        int generateId() {
            static std::random_device random;
            static std::mt19937 gen(random());
            static std::uniform_int_distribution<> dis(1, 99999);
            return dis(gen);
        }

        /**
         * @brief Validated and coverts name to lowercase
         * 
         * @param name name provided by user to check is it correct
         * @return name name of fish transformed to lower if its on fish list
         */

        static std::string fishNameCheck(std::string name) {

            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            if (hk::FishTypeProvider::getFishType(name) != "unknown") {
                return name;
            }
            return "unknown";
        }

        /**
         * @brief Constructor of fish
         */
        
        Fish(std::string name, double l, double w, int h) : m_name(fishNameCheck(name)),
                                                            m_type(hk::FishTypeProvider::getFishType(name)),
                                                            m_length(l > 0 ? l : 0.0), m_weight(w > 0 ? w : 0.0),
                                                            m_hour((h >= 0 && h < 24) ? h : 0), m_id(generateId()) {}

    public:

        /**
         * @brief Virtual destructor of fish object
         */

        virtual ~Fish() {}

        virtual void showFish() const {
            std::cout << "Fish species: " << m_name << ", length: " << m_length << " cm " << ", weight: " << m_weight
                      << " kg ";
        }


    };
}

