#pragma once

#include <string>
#include <iostream>
#include "json.hpp"
#include <fstream>

/**
 * @brief Check if the year provided by user is the leap year
 * 
 * @param year The year to check
 * @return true if the year is leap, false if the year is not leap
 */

bool leapYear(const int &year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * @brief Check if the data format provided by user is correct.
 * 
 * Checking number of days in months
 * Check if the separation of days,months,year is '-'
 * Seperated values check for correct data
 * 
 * @param date The date to check
 * @return true if the date format is correct, false if not
 * 
 */

bool dataFormat(const std::string &date) {
    
    if (date.length() != 10) {
        std::cout << "Wrong length of date" << std::endl;
        return false;
    }
    if (date[2] != '-' || date[5] != '-') {
        std::cout << "Days, months, years must be separated by '-' " << std::endl;
        return false;
    }

    int d, m, y;
    try {
        d = std::stoi(date.substr(0, 2));
        m = std::stoi(date.substr(3, 2));
        y = std::stoi(date.substr(6, 4));
    } catch (...) {
        std::cout << "Data must contain only numbers and '-' " << std::endl;
        return false;
    }

    if (y < 2026 || y > 2050) {
        std::cout << "Please enter real year not 1800s or 2100s" << std::endl;
        return false;
    }

    if (m < 1 || m > 12) {
        std::cout << "Invalid month number" << std::endl;
        return false;
    }
    int days = 31;
    if (m == 4 || m == 6 || m == 9 || m == 11) {
        days = 30;
    } else if (m == 2) {
        if (leapYear(y)) {
            days = 29;
        } else {
            days = 28;
        }
    }

    if (d < 1 || d > days) {
        std::cout << "Invalid days number in month " << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Set precision to second place of comma and glue metric unit to it
 * 
 * If in running program we got value 3.900001, this function
 * make this value to 3,90 and glue unit to it for example 3.90 kg
 * 
 * @param value value to set precision
 * @param unit unit to glue to value
 * @return formated value 
 */

std::string formatValue(double value, std::string unit) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value << " " << unit;
    return ss.str();
}

