#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "include/Log.hpp"
#include "include/json.hpp"
#include "include/CoarseFish.hpp"
#include "include/Predator.hpp"
#include "include/CoarseFish.hpp"
#include "include/dataFormat.hpp"


int main(){
    int selected;
    int start_hour;
    std::string date, place, weather;
    nlohmann::json jsonLogs;
    std::string jsonPath = "./logs/test.json";
            std::ifstream jsonIn(jsonPath);
            if(jsonIn.is_open()){
                try{
                    jsonIn >> jsonLogs;
                } catch(...){
                    jsonLogs = nlohmann::json::object();
                }
                jsonIn.close();
            }

    std::cout << "         Select options " << std::endl;
    std::cout << "1. New Log " << std::endl;
    std::cout << "2. Edit Log " << std::endl;
    std::cout << "3. Delete log" << std::endl;
    std::cout << "4. Records" << std::endl;
    std::cout << "5. History" << std::endl;
    std::cin >> selected;

    switch(selected) {
        case 1:{
            system("cls");
            std::cout << "Creating a new Log: " << std::endl;
            std::cout << "Enter date(day-month-year): "; 
            std::cin >> date;
            if(!dataFormat(date)){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                return 1;
            }
            std::cout << "Enter the fishing start hour: ";
            std::cin >> start_hour;
            std::cout << "Enter place: ";
            std::getline(std::cin >> std::ws, place);
            std::cout << "Enter weather: ";
            std::getline(std::cin >> std::ws, weather);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            hk::Log wpis(date, start_hour, place, weather);
            if(wpis.getPlace() != "unknown" && wpis.getWeather() != "unknown" && wpis.getHour() != 0){
                std::cout << "Data downloaded " << std::endl;
            } else {
                std::cout << "There is a problem" << std::endl;
            }
            std::string dateKey = wpis.getDate();
            jsonLogs["log"][dateKey] = wpis;
            jsonLogs["log"][dateKey]["fishes"] = nlohmann::json::array();
            

            std::ofstream jsonOut(jsonPath);
            if (jsonOut.is_open()) {
            jsonOut << std::setw(4) << jsonLogs;
            jsonOut.close();
            std::cout << "Data saved to file." << std::endl;
            }
            std::cin.get();
            break;
        }
        case 2:{
            system("cls");

            std::cout << "Editing existing log" << std::endl;
            std::cout << "Please enter a date to edit log: ";
            std::cin >> date;
            //std::string jsonPath = "logs/test.json";
           // std::cout << jsonPath << std::endl;
            if (std::filesystem::exists(jsonPath)){
                system("cls");
                int selectEdit;

                std::ifstream jsonFileStream(jsonPath);
                nlohmann::json jsonData = nlohmann::json::parse(jsonFileStream);

                if(jsonData["log"].contains(date)){

                //std::cout << "There isnt " << date << " to edit" << std::endl;
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
                        std::cout << "Current open log hour is: " << jsonData["log"][date]["open log hour"] << std::endl;
                        std::cout << "Current place is: " << jsonData["log"][date]["place"] <<std::endl;
                        std::cout << "Current weather is: " << jsonData["log"][date]["weather"] << std::endl << std::endl;
                        std::cout <<"To change parameter type parameter,new_value: " <<std::endl;
                        std::cout << "For example to set new weight: weather,sunny" << std::endl;
                        std::cout << "To exit type exit" << std::endl;
                        std::cout << std::endl;
                        
                        std::getline(std::cin >> std::ws, newSet);
                        if (newSet == "exit"){
                            std::cout << "Finished editing fishes" << std::endl;
                            break;
                        }

                        std::stringstream ss(newSet);
                        if(std::getline(ss,newParam, ',')){
                            std::getline(ss,newValue);
                        }
                        if(newParam == "place"){
                            jsonData["log"][date]["place"] = newValue;
                            std::cout << "Place updated" << std::endl;
                        }

                        else if(newParam == "weather"){
                            jsonData["log"][date]["weather"] = newValue;
                            std::cout << "Weather updated" << std::endl;
                        }
                        else if(newParam == "open_log_hour"){

                            if (std::stoi(newValue) >=0 && std::stoi(newValue) <24){
                                jsonData["log"][date]["open log hour"] = std::stoi(newValue);
                                std::cout << "Hour updated" <<std::endl;
                            } else {
                                std::cout << "Hour must be value of 0 to 23" << std::endl;
                                break;
                            }
                        } else {
                            std::cout << "Invalid option" << std::endl;
                            break;
                        }
                    }

                        std::ofstream jsonOut(jsonPath);
                        jsonOut << std::setw(4) << jsonData;
                        break;
                    }
                    
                    case 2:{

                        int hour;
                        std::string name;
                        double weight, length;
                        std::string lure;
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
                            std::cout <<"Enter weight: ";
                            std::cin >> weight;
                            std::cout << "Enter length: ";
                            std::cin >> length;
                            std::cout << "Enter hour: ";
                            std::cin >> hour;
                            hk::FishBase fish(name);
                            if(fish.getType() == "Predator"){
                                std::cout << "Enter lure";
                                std::getline(std::cin >> std::ws, lure);
                                hk::Predator predator(hour, name, length, weight, lure);
                                jsonData["log"][date]["fishes"].push_back(predator);
                            } else {
                                std::cout << "Enter lure";
                                std::getline(std::cin >> std::ws, lure);
                                std::cout << "enter groundbait";
                                std::getline(std::cin >> std::ws, gb);
                                hk::CoarseFish coarse(name,length,weight,hour,lure,gb);
                                jsonData["log"][date]["fishes"].push_back(coarse);
                            }
                    }

                        
                        std::ofstream jsonOut(jsonPath);
                             if (jsonOut.is_open()) {
                                jsonOut << std::setw(4) << jsonData;
                                jsonOut.close();
                                std::cout << "Data saved to file." << std::endl;
                            } else {
                                std::cout << "Error" << std::endl;
                            }
                       break;
                    }
                    
                    case 3:{

                        int id;
                        std::string newSet;
                        std::string newParam;
                        std::string newValue;
                        

                        system("cls");
                        std::cout << "Fishes catched at: " << date << std::endl;

                        auto& fishArray = jsonData["log"][date]["fishes"];

                        if(fishArray.empty()){
                            std::cout << "There arent fishes for this day" << std::endl;
                        } else {
                            for ( const auto& fish : fishArray){
                                std::cout << "ID: " << fish.value("id", 0)  << " | species: " << fish.value("name","unknown") << ", length: " << fish.value("length", 0.0) << " cm " << " ,weight: " << fish.value("weight", 0.0);
                                std::cout <<  std::endl;
                            }
                        }

                        std::cout << "Enter ID of fish to edit: " << std::endl;
                        std::cin >> id;
                        while(true){
                        system("cls");
                        std::cout << "Fish ID: " << id << std::endl;

                        for( auto& fish : fishArray){
                            if(fish.value("id",0) == id){
                                std::cout << std::setw(4) << fish;
                            }
                        }
                        std::cout << std::endl;
                        std::cout <<"To change parameter type parameter,new_value: " <<std::endl;
                        std::cout << "For example to set new weight: weight,10" << std::endl;
                        std::cout << "To exit type exit" << std::endl;
                        std::cin >> newSet;
                        if (newSet == "exit"){
                            std::cout << "Finished editing fishes" << std::endl;
                            break;
                        }
                        std::stringstream ss(newSet);

                        if(std::getline(ss,newParam, ',')){
                            std::getline(ss,newValue);
                        }
                        std::cout << newParam << std::endl;
                        std::cout << newValue << std::endl;

                        for( auto& fish : fishArray){
                            if(fish.value("id",0) == id){
                                if(newParam == "weight" || newParam == "length"){
                                    fish[newParam] = std::stod(newValue);
                                }
                            }
                            if(newParam == "hour"){
                                if(!(std::stoi(newValue) >= 0 && std::stoi(newValue) <24)){
                                    std::cout << "Hour must be 0 to 23 value" << std::endl;
                                    continue;
                                }
                                fish[newParam] = std::stoi(newValue);
                            }
                            if(newParam == "lure"){
                                fish[newParam] = newValue;
                            }
                            if(fish.value("type","unknown") == "Coarse_Fish"){
                                if(newParam == "ground_bait"){
                                    fish[newParam] = newValue;
                                }
                            }
                        }
                    }

                        std::ofstream jsonOut(jsonPath);
                        jsonOut << std::setw(4) << jsonData;
                        
                        break;
                    }
                    
                    case 4:{
                        int id;
                        char ans;
                        int toDelete;
                        

                        system("cls");
                        std::cout << "Fishes catched at: " << date << std::endl;

                        auto& fishArray = jsonData["log"][date]["fishes"];

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

                        std::ofstream jsonOut(jsonPath);
                        jsonOut << std::setw(4) << jsonData;
                       

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
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                        break;
                        }



                        if(jsonData["log"].contains(newDate)){
                            std::cout << "Log already exist, please delete or edit it" << std::endl;
                        } else {
                            jsonData["log"][newDate] = jsonData["log"][date];
                            jsonData["log"][newDate]["date"] = newDate;
                            jsonData["log"].erase(date);

                            std::ofstream jsonOut(jsonPath);
                            jsonOut << std::setw(4) << jsonData;
                            std::cout << "Succesfuly changed date from: " << date << " to new date: " << newDate << std::endl;
                        }

                        break;
                    }
                    default: break;
                }
                } else {
                    std::cout << "Log doesnt exist" << std::endl;
                }


                
            } 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 3: {

            char choice;

            system("cls");
            
            std::cout << "Delet log" << std::endl;
            std::cout << "Please enter a date to delete: ";
            std::cin >> date;
            if(!std::filesystem::exists(jsonPath)){
                std::cout << "Logs file error" << std::endl;
            }
            system("cls");
            std::ifstream jsonFileStream(jsonPath);
            nlohmann::json jsonData = nlohmann::json::parse(jsonFileStream);

            if(jsonData["log"].contains(date)){
                std::cout << "Log exist"<< std::endl;
                std::cout <<"Are you sure to delete: " << date << " log[y/n]: ";
                std::cin >> choice;
                if(choice == 'y' ){
                    jsonData["log"].erase(date);

                    std::ofstream jsonOut(jsonPath);
                    jsonOut << std::setw(4) << jsonData;
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
            break;
        }
        case 4: {
            system("cls");
            std::cout << "Your personal records" << std::endl;
            std::cout << std::endl;
            std::ifstream jsonFileStream(jsonPath);
            nlohmann::json jsonRecords = nlohmann::json::parse(jsonFileStream);

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

            for (const auto& [dateKey, dateLog] : jsonRecords["log"].items()){
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
            std::cout <<"Longest: " << longestCoarse->at("name").get<std::string>() << " " <<  longestCoarse->at("length").get<double>() << " cm " << ",lure: " << longestCoarse->at("lure").get<std::string>();
            std::cout << " ,ground bait: " << longestCoarse->at("ground_bait").get<std::string>() << " ,date: " << coarseLongestDate << std::endl;
            }
            if(heaviestCoarse != nullptr){
            std::cout <<"Heaviest: " << heaviestCoarse->at("name").get<std::string>() << " " << heaviestCoarse->at("weight").get<double>() << " kg " << ",lure: " << heaviestCoarse->at("lure").get<std::string>();
            std::cout << " ,ground bait: " << heaviestCoarse->at("ground_bait").get<std::string>() << " ,date: " << coarseHeaviestDate << std::endl;
            } else {
                std::cout << "No record found." << std::endl;
            }

            break;
        }

        case 5:{
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
            for(const auto& [dateKey, dateLog] : jsonLogs["log"].items()){
                std::cout << std::endl;
                std::cout << std::left
                << std::setw(wIndex) << "Num"
                << std::setw(wName) << "Fish species"
                << std::setw(wLen) << "Length"
                << std::setw(wWeight) << "Weight"
                << std::setw(wLure) << "Lure"
                << "Ground Bait" << std::endl;
                std::cout << std::string(wIndex + wName + wLen + wWeight + wLure + wGround, '-') << std::endl;

                

                for(const auto& fish : dateLog["fishes"]){

                    std::string formatedLength = formatValue(fish.value("length", 0.0), "cm");
                    std::string formatedWeight = formatValue(fish.value("weight", 0.0), "kg");

                    std::string groundBait = "-";
                    if(fish.value("type", "unknown") == "Coarse_Fish"){
                       groundBait = fish.value("ground_bait","unknown");
                    }
                
                    std::cout << std::left
                    << std::setw(wIndex) << std::to_string(index) + "."
                    << std::setw(wName) << fish.value("name", "unknown")
                    << std::setw(wLen) << formatedLength
                    << std::setw(wWeight) << formatedWeight
                    << std::setw(wLure) << fish.value("lure", "unknown") 
                    << groundBait << std::endl;
                    
                    index++;
                } 
                index = 1;
                std::cout<<"--------------------------------------------------" << std::endl;
                
            } 

            break;
        } 
        default: break;
            
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}