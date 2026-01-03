#pragma once
#include <iostream>
#include <string>
#include "json.hpp"

namespace hk{

class Log {
protected:
    std::string m_date;
    std::string m_place, m_weather;
    int m_hour;
public:
    Log(){
        m_date = "unknown";
        m_place = "unknown";
        m_weather = "unknown";
        m_hour = 0;
    }

    Log(std::string d, int h, std::string p, std::string w) : m_date(d.empty() ? "unknown" : d), m_place(p.empty() ? "unknown" : p), m_weather(w.empty() ? "unknown" : w), m_hour((h >=0 && h<24) ? h : 0) {}


    virtual ~Log(){};

    friend void to_json(nlohmann::json& j, const Log& l) {
        j = nlohmann::json{
            {"date", l.m_date},
            {"open_log_hour", l.m_hour},
            {"place", l.m_place},
            {"weather", l.m_weather}
            };
    }

    void setDate(std::string new_date){
        if (!new_date.empty()){
            m_date = new_date;
        } else {
            m_date = "unknown";
            std::cout << "invalid date" << std::endl;
        }
    }

    const std::string getDate() {
        return m_date;
    } 

    void setHour(int new_hour){
        if(new_hour >= 0 && new_hour < 24){
            m_hour = new_hour;
        } else {
            m_hour = 0;
        }
    }

    const std::string getPlace(){
        return m_place;
    }

    const std::string getWeather(){
        return m_weather;
    }

    const int getHour(){
        return m_hour;
    }



};
}