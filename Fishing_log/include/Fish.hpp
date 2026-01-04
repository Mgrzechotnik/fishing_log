#pragma once
#include <random>
#include "FishBase.hpp"

namespace hk{

class Fish : public FishBase {
protected:
    double m_weight;
    double m_length;
    int m_hour;
    int m_id;

    int generateId(){
        static std::random_device random;
        static std::mt19937 gen(random());
        static std::uniform_int_distribution<> dis(1, 99999);
        return dis(gen);
    }

    ///Generate unique id for fishes
    ///The chance of get two the same id in one fishing session is nearly equal to 0

    Fish(std::string name, double l, double w, int h) : FishBase(name), m_length(l > 0 ? l : 0.0), m_weight(w > 0 ? w : 0.0), m_hour((h >=0 && h<24) ? h : 0), m_id(generateId()){}

    ///Class for derived classes

public:

    virtual ~Fish() {}

    virtual void showFish() const {
        std::cout << "Fish species: " << m_name  << ", length: " << m_length << " cm " << ", weight: " << m_weight << " kg ";
    }

    

    void setId(int id){
        if(id > 0 && id <= 99999){
            m_id = id;
        }else {
            std::cout << "Invalid id value" << std::endl;
        }
    }

    void setWeight(double new_weight) {
        if (new_weight < 0){
             m_weight = 0.0;
             std::cout << "Invalid weight value" << std::endl;
        } else {
        m_weight = new_weight;
        }
    }

    void setLength(double new_length) {
        if (new_length < 0) {
            m_length = 0.0;
            std::cout << "Invalid length value" << std::endl;
        } else {
            m_length = new_length;
        }
    }

    void setHour(int new_hour){
        if(new_hour >= 0 && new_hour < 24){
            m_hour = new_hour;
        } else {
            m_hour = 0;
        }
    }

    int getId() const{
        return m_id;
    }

    bool operator==(const Fish& other) const {
        return this->m_id == other.m_id;
    }

};
}

///Base topology of fish. Fish receive unique Id, and base attributes