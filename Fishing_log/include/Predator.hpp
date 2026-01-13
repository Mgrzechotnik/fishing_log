#pragma once
#include "Fish.hpp"

namespace hk{

/**
 * @brief Represents a predatory fish
 * 
 * Inherits from the Fish class and add sppecific attribute lure
 */

class Predator : public Fish {
protected:
    /**
     * @brief The type of lure
     */
    std::string m_lure;


public:

    /**
     * @brief Constructor a new Predator object.
     * 
     * Initializes the fish properties and the lure. If the lure string 
     * is empty, it defaults to "unknown"
     * 
     * @param h The hour when the fish was caught
     * @param n The species name of the fish
     * @param l The length of the fish
     * @param w The weight of the fish
     * @param lur The name of the lure used
    */

    Predator(int h, std::string n, double l, double w, std::string lur) : Fish(n,l,w,h), m_lure(lur.empty() ? "unknown" : lur) {}

    /**
    * @brief Virtual destructor
    */

    virtual ~Predator() {}

    /**
    * @brief Serializes the log object to JSON
    */

    friend void to_json(nlohmann::json& j, const Predator& p) {
        j = nlohmann::json{{"type", p.m_type}, {"lure", p.m_lure}, {"id", p.m_id}, {"hour", p.m_hour}, {"name", p.m_name}, {"weight", p.m_weight}, {"length", p.m_length}};
    }


};
}

