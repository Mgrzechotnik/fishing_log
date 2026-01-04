#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "Log.hpp"
#include "json.hpp"
#include "CoarseFish.hpp"
#include "Predator.hpp"
#include "CoarseFish.hpp"
#include "dataFormat.hpp"

namespace hk {
class LogManager {
private:
    nlohmann::json m_jsonData;
    std::string m_jsonPath;

public:
    LogManager(std::string p) : m_jsonPath(p) {
        load();
    }

    void load(){
      std::ifstream jsonIn(m_jsonPath);
        if(jsonIn.is_open()){
            try{
                jsonIn >> m_jsonData;

                if(!m_jsonData.contains("log")){
                    m_jsonData["log"] = nlohmann::json::object();
                }
            } catch(...){
                m_jsonData = nlohmann::json::object();
                m_jsonData["log"] = nlohmann::json::object();
            }
            jsonIn.close();
        } else {
            m_jsonData = nlohmann::json::object();
            m_jsonData["log"] = nlohmann::json::object();
        }
    }

    void save(){
        std::ofstream jsonOut(m_jsonPath);

        if(jsonOut.is_open()){
            jsonOut << std::setw(4) << m_jsonData;
            jsonOut.close();
        }
    }

    void clearInput(){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    template <typename T>
    T checkInput(const std::string& input){
        T value;
        while(true){
            std::cout << input;
            if(std::cin >> value){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else{
                std::cout << "Invalid data input" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    template <typename T>
    T checkValue(std::string& input, bool& accept){
        std::istringstream ss(input);
        T value;
        if( ss >> value && ss.eof()){
            accept = true;
            return value;
        } else{
            accept = false;
            return T();
        }
    }

    
    

    void createNewLog(){

        int start_hour;
        std::string date, place, weather;

        while(true){

        system("cls");
        std::cout << "Creating a new Log: " << std::endl;
        std::cout << "Enter date(day-month-year): "; 
        std::cin >> date;

        if(!dataFormat(date)){
                std::cout << "To continue please press enter" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                continue;
        }

        start_hour = checkInput<int>("Enter start hour: ");
        if(start_hour < 0 || start_hour > 23){
            std::cout << "Invalid hour, must be 0 to 23 number" << std::endl;
            std::cout << "To continue please press enter" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            continue;
        }
        std::cout << "Enter place: ";
        std::getline(std::cin >> std::ws, place);
        std::cout << "Enter weather: ";
        std::getline(std::cin >> std::ws, weather);

        hk::Log new_log(date, start_hour, place, weather);
       
        std::string dateKey = new_log.getDate();
        m_jsonData["log"][dateKey] = new_log;
        m_jsonData["log"][dateKey]["fishes"] = nlohmann::json::array();
    
        save();
        std::cout << "Data saved to file." << std::endl;
        std::cout << "To continue please press enter" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("cls");
        break;
        
    }
   
    }

    void editLog(){

        std::string date;
        int selectEdit;

        system("cls");

        std::cout << "Editing existing log" << std::endl;
        std::cout << "Please enter a date to edit log: ";

        std::cin >> date;

        system("cls");

        if(m_jsonData["log"].contains(date)){

            std::cout << "Log exist" << std::endl;
            std::cout << "Select option" << std::endl;
            std::cout << "1. Change hours of opening log, weather, place" << std::endl;
            std::cout << "2. Add fishes" << std::endl;
            std::cout << "3. Edit fishes" << std::endl;
            std::cout << "4. Delete fish" << std::endl;
            std::cout << "5. Change date" << std::endl;
            std::cin >> selectEdit;

            switch(selectEdit){
                case 1:{

                    int new_hour;
                    std::string newSet;
                    std::string newParam;
                    std::string newValue;

                    while(true){

                    system("cls");

                    std::cout << "Changing parameters of log date: " << date << std::endl;
                    std::cout << "Current open_log_hour is: " << m_jsonData["log"][date]["open_log_hour"] << std::endl;
                    std::cout << "Current place is: " << m_jsonData["log"][date]["place"] <<std::endl;
                    std::cout << "Current weather is: " << m_jsonData["log"][date]["weather"] << std::endl << std::endl;
                    std::cout <<"To change parameter type parameter,new_value: " <<std::endl;
                    std::cout << "For example to set new weight: weather,sunny" << std::endl;
                    std::cout << "To exit type exit" << std::endl;
                    std::cout << std::endl;
                    std::getline(std::cin >> std::ws, newSet);

                    if (newSet == "exit"){
                        std::cout << "Finished editing log" << std::endl;
                        break;
                    }

                    std::stringstream ss(newSet);

                    if(std::getline(ss,newParam, ',')){
                        std::getline(ss,newValue);
                    }

                    if(newParam == "place"){
                        m_jsonData["log"][date]["place"] = newValue;
                        std::cout << "Place updated" << std::endl;
                    }

                    else if(newParam == "weather"){
                        m_jsonData["log"][date]["weather"] = newValue;
                        std::cout << "Weather updated" << std::endl;
                    }

                    else if(newParam == "open_log_hour"){
                        bool success = false;
                        int newHour = checkValue<int>(newValue, success);
                        
                        if(!success){
                            std::cout << "Your: " << newValue << " isnt a number" << std::endl;
                            std::cout << "To continue please press enter" << std::endl;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        } else if(newHour < 0 || newHour > 23){

                            std::cout << "Invalid hour, must be 0 to 23 number" << std::endl;
                            std::cout << "To continue please press enter" << std::endl;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cin.get();
                            continue;
                         
                        } else {
                            m_jsonData["log"][date]["open_log_hour"] = newHour;
                        }
                    } else {
                        std::cout << "Invalid option" << std::endl;
                        break;
                    }
                }
                    save();
                    std::cout << "Hour updated" <<std::endl;
                    std::cout << "To continue please press enter" << std::endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    break;
                }
                
                case 2:{

                    int hour;
                    std::string name;
                    double weight, length;
                    std::string lure;
                    std::string bait;
                    std::string gb;

                    while(true){

                        system("cls");

                        std::cout << "Adding fishes"<< std::endl;
                        std::cout << std::endl;
                        std::cout << "To exit please type exit in fish species" << std::endl;
                        std::cout << std::endl;
                        std::cout << "Enter fish species: ";
                        std::getline(std::cin >> std::ws, name);

                        if (name == "exit"){
                            std::cout << "Finished adding fishes" << std::endl;
                            break;
                        }

                        weight = checkInput<double>("Enter weight: ");
                        length = checkInput<double>("Enter length: ");
                        hour = checkInput<double>("Enter hour: ");

                        if(hour < m_jsonData["log"][date]["open_log_hour"]){
                            std::cout << "Its illegal to write fish before start fishing" << std::endl;
                            std::cout << "Press enter to continue" << std::endl;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }

                        hk::FishBase fish(name);

                        if(fish.getType() == "Predator"){
                            std::cout << "Enter lure: ";
                            std::getline(std::cin >> std::ws, lure);
                            hk::Predator predator(hour, name, length, weight, lure);
                            m_jsonData["log"][date]["fishes"].push_back(predator);
                        } else {
                            std::cout << "Enter bait: ";
                            std::getline(std::cin >> std::ws, bait);
                            std::cout << "Enter ground bait: ";
                            std::getline(std::cin >> std::ws, gb);
                            hk::CoarseFish coarse(name,length,weight,hour,bait,gb);
                            m_jsonData["log"][date]["fishes"].push_back(coarse);
                        }
                        }
 
                            save();
                            std::cout << "Data saved to file." << std::endl;
                            break;
                        } 
                
                
                case 3:{

                    int id;
                    std::string newSet;
                    std::string newParam;
                    std::string newValue;
                    
                    system("cls");

                    std::cin.clear();

                    std::cout << "Fishes catched at: " << date << std::endl;

                    auto& fishArray = m_jsonData["log"][date]["fishes"];

                    if(fishArray.empty()){
                        std::cout << "There arent fishes for this day" << std::endl;
                        std::cout << "Press enter to continue" << std::endl;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                        break;
                    } else {
                        for ( const auto& fish : fishArray){
                            std::cout << "ID: " << fish.value("id", 0)  << " | species: " << fish.value("name","unknown") << ", length: " << fish.value("length", 0.0) << " cm " << " ,weight: " << fish.value("weight", 0.0);
                            std::cout <<  std::endl;
                        }
                    }

                    std::cout << "Enter ID of fish to edit: " << std::endl;
                    std::cin >> id;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                    while(true){

                    system("cls");

                    std::cout << "Fish ID: " << id << std::endl;

                    for( auto& fish : fishArray){
                        if(fish.value("id",0) == id){
                            std::cout << std::setw(4) << fish;
                        }
                    }
                    std::cout << std::endl;
                    std::cout << "You cant edit: id and name. To do this please delete fish and create new " << std::endl;
                    std::cout <<"To change parameter type parameter,new_value: " <<std::endl;
                    std::cout << "For example to set new weight: weight,10" << std::endl;
                    std::cout << "To exit type exit" << std::endl;
                    std::getline(std::cin, newSet);

                    if (newSet == "exit"){
                        std::cout << "Finished editing fishes" << std::endl;
                        break;
                    }

                    std::stringstream ss(newSet);

                    if(std::getline(ss,newParam, ',')){
                        std::getline(ss,newValue);
                    }

                    for( auto& fish : fishArray){
                        if(fish.value("id",0) == id){
                            if(newParam == "weight" || newParam == "length"){
                                bool success = false;
                                double dnewValue = checkValue<double>(newValue,success);
                                if(!success){
                                std::cout << "Your: " << newValue << " isnt a number" << std::endl;
                                std::cout << "To continue please press enter" << std::endl;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cin.get();
                                continue;
                                } else {
                                    if(dnewValue > 0){
                                        fish[newParam] = dnewValue;
                                        std::cout << newParam << " uptadated" << std::endl;
                                    } else {
                                        std::cout << newParam << " cant be less than zero " << std::endl;
                                        std::cout << "To continue please press enter" << std::endl;
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        std::cin.get();
                                        continue;
                                    }
                                }
                            }
                        
                            else if(newParam == "hour"){
                                bool success = false;
                                int newHour = checkValue<int>(newValue, success);

                                if(!success){
                                    std::cout << "Your: " << newValue << " isnt a number" << std::endl;
                                    std::cout << "To continue please press enter" << std::endl;
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    std::cin.get();
                                    continue;
                                } else{

                                    if (newHour >=0 && newHour <24){
                                        fish[newParam] = newHour;
                                        std::cout << "Hour updated" <<std::endl;
                                    } else {
                                        std::cout << "Hour must be value of 0 to 23" << std::endl;
                                        std::cout << "To continue please press enter" << std::endl;
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        std::cin.get();
                                        continue;
                                    }
                                }
                            }
                            else if(fish.value("type","unknown") == "Predator"){
                                if(newParam == "lure"){
                                    fish[newParam] = newValue;
                                }
                            }
                            else if(fish.value("type","unknown") == "Coarse_Fish"){
                                if(newParam == "ground_bait"){
                                    fish[newParam] = newValue;
                                }
                                if(newParam == "bait"){
                                    fish[newParam] = newValue;
                                }
                            }
                        } 
                    }
                    }
                    save();
                    break;
                }
                
                case 4:{
                    int id;
                    char ans;
                    int toDelete;
                    
                    system("cls");

                    std::cout << "Fishes catched at: " << date << std::endl;

                    auto& fishArray = m_jsonData["log"][date]["fishes"];

                    if(fishArray.empty()){
                        std::cout << "There arent fishes for this day" << std::endl;
                    } else {
                        for ( const auto& fish : fishArray){
                            std::cout << "ID: " << fish.value("id", 0)  << " | species: " << fish.value("name","unknown") << ", length: " << fish.value("length", 0.0) << " cm " << " ,weight: " << fish.value("weight", 0.0);
                            std::cout <<  std::endl;
                        }
                    }

                    std::cout << "Enter ID of fish to delete: " << std::endl;
                    std::cin >> id;

                    std::cout << "Fish ID: " << id << std::endl;

                    for(int i =0; i< fishArray.size(); i++){
                        if(fishArray[i].value("id", 0) == id);
                        toDelete = i;
                        break;
                    }

                    std::cout << std::setw(4) << fishArray[toDelete] << std::endl;
                    std::cout << "Are you sure to delete fish [y/n]: ";
                    std::cin >> ans;

                    if(ans =='y' || ans == 'Y'){
                        fishArray.erase(toDelete);
                        std::cout << "Fish deleted" << std::endl;
                    } else {
                        std::cout <<"Aborted" << std::endl;
                    }

                    save();
                    break;
                }
                case 5:{

                    std::string newDate;
                    int number;

                    system("cls");
                    std::cout <<"Editing log date" << std::endl << std::endl;
                    std::cout << "Current log date: " << date <<std::endl;
                    std::cout << "Enter new log date: ";
                    std::cin >> newDate;

                    if(!dataFormat(newDate)){
                        break;
                    }

                    if(m_jsonData["log"].contains(newDate)){
                        std::cout << "Log already exist, please delete or edit it" << std::endl;
                    } else {
                        m_jsonData["log"][newDate] = m_jsonData["log"][date];
                        m_jsonData["log"][newDate]["date"] = newDate;
                        m_jsonData["log"].erase(date);

                        save();
                        std::cout << "Succesfuly changed date from: " << date << " to new date: " << newDate << std::endl;
                    }

                    break;
                }
                default: break;
            }
            system("cls");
        } else {
            std::cout << "Log doesnt exist" << std::endl;
        }
}

void deleteLog(){
    char choice;
    std::string date;

    system("cls");
    
    std::cout << "Delet log" << std::endl;
    std::cout << "Please enter a date to delete: ";
    std::cin >> date;

    system("cls");

    if(m_jsonData["log"].contains(date)){
        std::cout << "Log exist"<< std::endl;
        std::cout <<"Are you sure to delete: " << date << " log[y/n]: ";
        std::cin >> choice;

        if(choice == 'y' ){
            m_jsonData["log"].erase(date);

            save();
            std::cout << "Succesfuly deleted a log: " << date << std::endl;
        }

        if(choice == 'n'){
            std::cout << "Aborted deleting log: " << date << std::endl;
        }

        if(choice != 'n' && choice != 'y') {
            std::cout << "Answer must be 'y' or 'n' " << std::endl;
            std::cout << "Failed to delete a log" << std::endl;
        }
    } else {
        std::cout << "Failed to find: " << date << " log" << std::endl;
    }
}

void recordsLog(){

    const nlohmann::json* longestPredator = nullptr;
    const nlohmann::json* heaviestPredator = nullptr;
    const nlohmann::json* longestCoarse = nullptr;
    const nlohmann::json* heaviestCoarse = nullptr;
    
    double predatorMaxLength = 0.0;
    double predatorMaxWeight = 0.0;
    double coarseMaxLength = 0.0;
    double coarseMaxWeight = 0.0;
    
    std::string predatorHeaviestDate;
    std::string predatorLongestDate;
    std::string coarseHeaviestDate;
    std::string coarseLongestDate;

    system("cls");

    std::cout << "Your personal records" << std::endl;
    std::cout << std::endl;
    
    for (const auto& [dateKey, dateLog] : m_jsonData["log"].items()){
        std::string currentDate = dateLog["date"];

        for (const auto& fish : dateLog["fishes"]){
            if(fish.contains("type") && fish["type"] == "Predator"){
                double currentLength = fish["length"];
                double currentWeight = fish["weight"];

                if(currentWeight > predatorMaxWeight){
                    predatorMaxWeight = currentWeight;
                    predatorHeaviestDate = currentDate;
                    heaviestPredator = &fish;
                }

                if(currentLength > predatorMaxLength){
                    predatorMaxLength = currentLength;
                    predatorLongestDate = currentDate;
                    longestPredator = &fish;
                }
            }
            if(fish.contains("type") && fish["type"] == "Coarse_Fish"){
                double currentLength = fish["length"];
                double currentWeight = fish["weight"];

                if(currentWeight > coarseMaxWeight){
                    coarseMaxWeight = currentWeight;
                    coarseHeaviestDate = currentDate;
                    heaviestCoarse = &fish;
                }

                if(currentLength > coarseMaxLength){
                    coarseMaxLength = currentLength;
                    coarseLongestDate = currentDate;
                    longestCoarse = &fish;
                }
            }
        }
    }

    std::cout << "Predators:" << std::endl;
    std::cout << std::endl;
    if (longestPredator != nullptr){
    std::cout <<"Longest: " << longestPredator->at("name").get<std::string>() << " " <<  longestPredator->at("length").get<double>() << " cm " << ",lure: " << longestPredator->at("lure").get<std::string>();
    std::cout << " ,date: " << predatorLongestDate << std::endl;
    }

    if(heaviestPredator != nullptr){
    std::cout <<"Heaviest: " << heaviestPredator->at("name").get<std::string>() << " " << heaviestPredator->at("weight").get<double>() << " kg " << ",lure: " << heaviestPredator->at("lure").get<std::string>();
    std::cout << " ,date: " << predatorHeaviestDate << std::endl;
    } else {
        std::cout << "No record found." << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Coarse fishes:" << std::endl;
    std::cout << std::endl;
    if(longestCoarse != nullptr){
    std::cout <<"Longest: " << longestCoarse->at("name").get<std::string>() << " " <<  longestCoarse->at("length").get<double>() << " cm " << ",bait: " << longestCoarse->at("bait").get<std::string>();
    std::cout << " ,ground bait: " << longestCoarse->at("ground_bait").get<std::string>() << " ,date: " << coarseLongestDate << std::endl;
    }

    if(heaviestCoarse != nullptr){
    std::cout <<"Heaviest: " << heaviestCoarse->at("name").get<std::string>() << " " << heaviestCoarse->at("weight").get<double>() << " kg " << ",bait: " << heaviestCoarse->at("bait").get<std::string>();
    std::cout << " ,ground bait: " << heaviestCoarse->at("ground_bait").get<std::string>() << " ,date: " << coarseHeaviestDate << std::endl;
    } else {
        std::cout << "No record found." << std::endl;
    }
}

void historyLog(){
    int index =1;
    const int wIndex = 4;
    const int wName = 15;
    const int wLen = 12;
    const int wWeight = 12;
    const int wLure = 20;
    const int wGround = 25;
    
    system("cls");

    std::cout << "History of logs" << std::endl;
    std::cout << std::endl;

    for(const auto& [dateKey, dateLog] : m_jsonData["log"].items()){
        std::cout << std::endl;
        std::cout << dateLog.value("date","unknown") << std::endl;
        std::cout << std::left
        << std::setw(wIndex) << "Num"
        << std::setw(wName) << "Fish species"
        << std::setw(wLen) << "Length"
        << std::setw(wWeight) << "Weight"
        << std::setw(wLure) << "Bait"
        << "Ground Bait" << std::endl;

        std::cout << std::string(wIndex + wName + wLen + wWeight + wLure + wGround, '-') << std::endl;

        for(const auto& fish : dateLog["fishes"]){

            std::string formatedLength = formatValue(fish.value("length", 0.0), "cm");
            std::string formatedWeight = formatValue(fish.value("weight", 0.0), "kg");

            std::string groundBait = "-";
            std::string bait = "-";
            if(fish.value("type", "unknown") == "Coarse_Fish"){
                groundBait = fish.value("ground_bait","unknown");
                bait = fish.value("bait","unknown");
                std::cout << std::left
                << std::setw(wIndex) << std::to_string(index) + "."
                << std::setw(wName) << fish.value("name", "unknown")
                << std::setw(wLen) << formatedLength
                << std::setw(wWeight) << formatedWeight
                << std::setw(wLure) << bait 
                << groundBait << std::endl;
            } else {
                std::cout << std::left
                << std::setw(wIndex) << std::to_string(index) + "."
                << std::setw(wName) << fish.value("name", "unknown")
                << std::setw(wLen) << formatedLength
                << std::setw(wWeight) << formatedWeight
                << std::setw(wLure) << fish.value("lure", "unknown") 
                << groundBait << std::endl;
            }
        
            
            
            index++;
        } 
        index = 1;
        std::cout<<"--------------------------------------------------" << std::endl;
        
    } 

}

void showMenu(){
    std::cout << "         Select options " << std::endl;
    std::cout << "1. New Log " << std::endl;
    std::cout << "2. Edit Log " << std::endl;
    std::cout << "3. Delete log" << std::endl;
    std::cout << "4. Records" << std::endl;
    std::cout << "5. History" << std::endl;
}

};
}