#pragma once
#include <string>
#include <iostream>
#include "json.hpp"
#include <fstream>

bool leapYear(const int& year){
    return (year % 4 == 0 && year % 100 != 0 ) || (year % 400 == 0);
}

bool dataFormat(const std::string& date){
    std::ifstream jsonInput("./logs/your_log.json");
    if (!jsonInput.is_open()) {
        std::cerr << "Error: Could not open your_log.json" << std::endl;
        return "unknown";
    }
    nlohmann::json jsonData = nlohmann::json::parse(jsonInput);

    if(jsonData["log"].contains(date)){
        std::cout << "Log already exist please edit or delete log" << std::endl;
        return false;
    }

    if(date.length() != 10){
            std::cout << "Wrong length of date" << std::endl;
            return false;
        }
        if(date[2] != '-' || date[5] != '-'){
            return false;
            std::cout << "Days, months, years must be separated by '-' " << std::endl;
        }

        int d, m, y;
        try{
            d = std::stoi(date.substr(0,2));
            m = std::stoi(date.substr(3,2));
            y = std::stoi(date.substr(6,4));
        } catch(...){
            std::cout << "Data must contain only numbers and '-' " <<std::endl;
            return false; 
        }

        if(y < 2026 || y > 2050){
            std::cout << "Please enter real year not 1800s or 2100s" << std::endl;
            return false;
        }

        if(m < 1 || m > 12){
            std::cout << "Invalid month number" << std::endl;
            return false;
        }
        int days = 31;
        if(m == 4 || m == 6 || m == 9 || m == 11){
            days = 30;
        } else if (m == 2){
            if(leapYear(y)){
                days = 29;
            } else {
                days = 28;
            }
        }

        if(d < 1 || d > days){
            std::cout << "Invalid days number in month " << std::endl;
            return false;
        }
        return true;
}

std::string formatValue(double value, std::string unit) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value << " " << unit;
    return ss.str();
}