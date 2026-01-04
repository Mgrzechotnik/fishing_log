#pragma once
#include "Fish.hpp"

namespace hk{

class Predator : public Fish {
protected:
    std::string m_lure;
public:
    Predator(int h, std::string n, double l, double w, std::string lur) : Fish(n,l,w,h), m_lure(lur.empty() ? "unknown" : lur) {}


    virtual ~Predator() {}

    friend void to_json(nlohmann::json& j, const Predator& p) {
        j = nlohmann::json{{"type", p.m_type}, {"lure", p.m_lure}, {"id", p.m_id}, {"hour", p.m_hour}, {"name", p.m_name}, {"weight", p.m_weight}, {"length", p.m_length}};
    }

    void showFish() const override {
        Fish::showFish();
        std::cout << ", Lure: " << m_lure << std::endl;
    }

    void setLure(std::string new_lure){
        if(new_lure.size() <= 0){
            std::cout << "Empty name of lure" << std::endl;
            m_lure = "unknown";
        } else {
            m_lure = new_lure;
        }
    }
};
}

    ///Derived class for predatory fishes only
