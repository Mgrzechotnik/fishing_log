#pragma once
#include <fstream>
#include <cctype>
#include <iostream>
#include "json.hpp"


std::string checkName(const std::string& name){
    std::ifstream jsonInput("./fish_list/fishList.json");
    if (!jsonInput.is_open()) {
        std::cerr << "Error: Could not open fishList.json" << std::endl;
        return "unknown";
    }
    nlohmann::json jsonData = nlohmann::json::parse(jsonInput);
    

    std::string sname = name;

    std::transform(sname.begin(), sname.end(), sname.begin(), ::tolower);

    for (auto it = jsonData.begin(); it != jsonData.end(); it++){
        for(auto &fish : it.value()){
            if (sname == fish){
                //std::cout << "Fish exist" << std::endl;
                return sname;
            }
        }
    }

    std::cout << "There is no fish named: " << name << std::endl;
    return "unknown";
}

///Read from fishList.json
///Checking if the input fish exists on the national species list.
///Prevents of creating spelling mistakes


std::string checkType(const std::string& name){
    std::ifstream jsonInput("./fish_list/fishList.json");
    if (!jsonInput.is_open()) {
        std::cerr << "Error: Could not open fishList.json" << std::endl;
        return "unknown";
    }
    nlohmann::json jsonData = nlohmann::json::parse(jsonInput);

    for (auto it = jsonData.begin(); it != jsonData.end(); it ++){
        for(auto& fish : it.value()){
            if(name == fish){
                //std::cout << "Category exists" << std::endl;
                return it.key();
            }
        }
    }

    std::cout << "There is no type of this fish" << std::endl;
    return "unknown";
    
}

///Check type of fish, is it predator or corase fish

