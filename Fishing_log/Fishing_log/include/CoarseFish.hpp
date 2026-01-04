#pragma once
#include "Fish.hpp"

namespace hk{

class CoarseFish : public Fish {
protected:
    std::string m_bait;
    std::string m_groundBait;
public:
    CoarseFish(std::string n, double l, double w, int h, std::string lur, std::string g) : Fish(n,l,w,h), m_bait(lur.empty() ? "unknown" : lur), m_groundBait(g.empty() ? "unnknown" : g) {}

    virtual ~CoarseFish() {}

    friend void to_json(nlohmann::json& j, const CoarseFish& c) {
        j = nlohmann::json{{"type", c.m_type}, {"id", c.m_id}, {"hour", c.m_hour}, {"name", c.m_name}, {"weight", c.m_weight}, {"length", c.m_length}, {"bait", c.m_bait}, {"ground_bait",c.m_groundBait}};
    }

    void showFish() const override {
        Fish::showFish();
        std::cout << "Lure: " << m_bait << ", Ground bait: " << m_groundBait << std::endl;
    }

    void setBait(std::string new_bait){
        if(new_bait.size() <= 0){
            std::cout << "Empty name of bait" << std::endl;
            m_bait = "unknown";
        } else {
            m_bait = new_bait;
        }
    }

    void setGroundBait(std::string new_gb){
        if(new_gb.size() <= 0){
            std::cout << "Empty name of ground bait" << std::endl;
            m_groundBait = "unknown";
        } else {
            m_groundBait = new_gb;
        }
    }
};
}

///Derived class for coarse fishes only