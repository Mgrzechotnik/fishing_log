#pragma once
#include <iostream>
#include <string>
#include "json.hpp"

namespace hk{

/**
 * @brief Base class representing a general log entry
 * 
 * Stores basic information about log, including date, hour, location, weather.
 * It serves as a base for more specific log types.
 */
class Log {
protected:
    /**
     * @brief The date of the log entry
     */
    std::string m_date;
    /**
     * @brief The location and weather of the log entry
     */
    std::string m_place, m_weather;
    /**
     * @brief The start hour of log
     */
    int m_hour;
public:

    /**
     * @brief Defalut constructor
     * 
     * Initialize all string fields and hour
     */
    Log(){
        m_date = "unknown";
        m_place = "unknown";
        m_weather = "unknown";
        m_hour = 0;
    }

    /**
     * @brief Parametrized constructor with validation
     * 
     * Creates a log entry with given data.
     * If data is incorrect, set default value.
     * 
     * @param d The date of log entry
     * @param h The start hour of log entry
     * @param p The location of the log entry
     * @param w The weather condition
     */

    Log(std::string d, int h, std::string p, std::string w) : 
    m_date(d.empty() ? "unknown" : d), m_place(p.empty() ? "unknown" : p), m_weather(w.empty() ? "unknown" : w),
    m_hour((h >=0 && h<24) ? h : 0) {}


    /**
     * @brief Virtual destructor
     * 
     */

    virtual ~Log(){};

    /**
     * @brief Serializes the log object to JSON
     */

    friend void to_json(nlohmann::json& j, const Log& l) {
        j = nlohmann::json{
            {"date", l.m_date},
            {"open_log_hour", l.m_hour},
            {"place", l.m_place},
            {"weather", l.m_weather}
            };
    }

    /**
     * @brief Retrives the date of the log entry
     */

    const std::string getDate() {
        return m_date;
    } 

};
}

