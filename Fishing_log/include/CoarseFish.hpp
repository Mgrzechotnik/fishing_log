#pragma once
#include "Fish.hpp"

namespace hk{

/**
 * @brief Represents a coarse fish.
 * 
 * Inherits from the Fish class and adds a specific attribute for the bait and groundbait 
 * used to catch the fish.
 */

class CoarseFish : public Fish {
protected:
    /**
     * @brief The type of bait
     */
    std::string m_bait;
    /**
     * @brief The type of groundbait
     */
    std::string m_groundBait;
public:
    /**
     * @brief Constructor a new Coarse Fish object.
     * 
     * Initializes the fish properties, lure and ground bait. If the lure and groudbait string 
     * is empty, it defaults to "unknown"
     * 
     * @param h The hour when the fish was caught
     * @param n The species name of the fish
     * @param l The length of the fish
     * @param w The weight of the fish
     * @param lur The name of the bait used
     * @param g The name of the ground bait used
     * 
    */

    CoarseFish(std::string n, double l, double w, int h, std::string lur, std::string g) : Fish(n,l,w,h), m_bait(lur.empty() ? "unknown" : lur), m_groundBait(g.empty() ? "unnknown" : g) {}

    /**
    * @brief Destructor for CoarseFish
    */

    virtual ~CoarseFish() {}

    /**
    * @brief Serializes the log object to JSON
    */

    friend void to_json(nlohmann::json& j, const CoarseFish& c) {
        j = nlohmann::json{{"type", c.m_type}, {"id", c.m_id}, {"hour", c.m_hour}, {"name", c.m_name}, {"weight", c.m_weight}, {"length", c.m_length}, {"bait", c.m_bait}, {"ground_bait",c.m_groundBait}};
    }

};
}

///Derived class for coarse fishes only