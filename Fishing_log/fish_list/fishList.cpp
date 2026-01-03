#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>
//#include <limits>


int main(){
    

    nlohmann::json jsonFish;
    jsonFish["Predator"] = nlohmann::json::array();
    jsonFish["Coarse_Fish"] = nlohmann::json::array(); 

    std::ifstream file("fish_species_list.txt");
        if (!file.is_open()) {
            std::cerr << "Failed to open file" << std::endl;
            return 1;
        }
    std::string line;
    while(std::getline(file,line)){
        if (line.empty()) 
            continue;
        std::stringstream ss(line);
        std::string name;
        std::string type;
        
        if(std::getline(ss, name, ',')){
            std::getline(ss, type);
                if (type == "P"){
                    jsonFish["Predator"].push_back(name);
                }else{
                    jsonFish["Coarse_Fish"].push_back(name);
                }
            
        }
    }

    std::ofstream jsonOut("./fishList.json");
    jsonOut << std::setw(4) << jsonFish;




    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}
