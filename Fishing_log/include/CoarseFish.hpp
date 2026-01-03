#pragma once
#include "Fish.hpp"

namespace hk{

class CoarseFish : public Fish {
protected:
    std::string m_lure;
    std::string m_groundBait;
public:
    CoarseFish(std::string n, double l, double w, int h, std::string lur, std::string g) : Fish(n,l,w,h), m_lure(lur.empty() ? "unknown" : lur), m_groundBait(g.empty() ? "unnknown" : g) {}

    virtual ~CoarseFish() {}

    friend void to_json(nlohmann::json& j, const CoarseFish& c) {
        j = nlohmann::json{{"type", c.m_type}, {"id", c.m_id}, {"hour", c.m_hour}, {"name", c.m_name}, {"weight", c.m_weight}, {"length", c.m_length}, {"lure", c.m_lure}, {"ground_bait",c.m_groundBait}};
    }

    void showFish() const override {
        Fish::showFish();
        std::cout << "Lure: " << m_lure << ", Ground bait: " << m_groundBait << std::endl;
    }

    void setLure(std::string new_lure){
        if(new_lure.size() <= 0){
            std::cout << "Empty name of lure" << std::endl;
            m_lure = "unknown";
        } else {
            m_lure = new_lure;
        }
    }

    void setGroundBait(std::string new_gb){
        if(new_gb.size() <= 0){
            std::cout << "Empty name of lure" << std::endl;
            m_groundBait = "unknown";
        } else {
            m_groundBait = new_gb;
        }
    }
};
}