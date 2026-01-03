#pragma once
#include "CheckFish.hpp"
namespace hk{

class FishBase{
protected:
    std::string m_name;
    std::string m_type;
    
public:
    FishBase(std::string n) {
        m_name = checkName(n);
        m_type = checkType(n);
    }

    const std::string getName(){
        return m_name;
    }

    const std::string getType(){
        return m_type;
    }

};
}