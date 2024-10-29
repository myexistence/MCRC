//
// Created by Coding on 10/29/24.
//

#include <iostream>
#include "parseProc.h"

using std::cout;
using std::cin;

namespace parse {
    void parseProc::addBaseItem(const std::string& name) {
        auto id = nextJsonID();
        database["basicItems"].push_back({
        {"name",name},
        {"id",id}
        });
    }

    int parseProc::matchID(const std::string &nameMatch){
        if(!checkJsonNameExists(nameMatch) == true){
            std::cerr<<"ERROR: Tried to match " << nameMatch << " and it doesn't exist"<<std::endl<<"EXITING";
            return -1;
        }
        for (const auto& it : database["baseItems"])
            if(it["name"] == nameMatch)
                return  it["id"];
        for (const auto& it : database["recipes"])
            if(it["name"] == nameMatch)
                    return  it["id"];
        std::cerr << "ERROR: "<< nameMatch << " exists but has no matching ID" << std::endl << "EXITING";
        return -1;
    }

    nlohmann::json parseProc::createPrecursorInput(const std::pmr::vector<precursor::precursorToken>& precursors) {
        nlohmann::json holdPrecursor = nlohmann::json::array();
        for (const auto& it: precursors) {
            holdPrecursor.push_back({
                {"amount", it.precursorAmount},
                {"id", matchID(it.precursorName)}
            });
        }
        return holdPrecursor;
    }


    void parseProc::amendRecipe(const std::string& recipe, int) {
    }
    void parseProc::addRecipe(precursor::precursorToken& parent,
        const std::pmr::vector<precursor::precursorToken>& precursors) {

        auto nextID = nextJsonID();
        database["recipes"].push_back({
        {"amount", 1 /*parent.yield create yield member in precursorToken*/},
        {"id", nextID},
        {"name", parent.precursorName},
        {"precursors", createPrecursorInput(precursors)}});
    }

    bool parseProc::checkJsonNameExists(const std::string& name) {
        for (const auto& it: database["basicItems"])
            if(it["name"]== name)
                return true;
        for(const auto& it : database["recipes"])
            if(it["name"] == name)
                return true;
        return false;
    }
    int parseProc::nextJsonID() {
        size_t idCount = 0;
        idCount += database["basicItems"].size();
        idCount += database["recipes"].size();
        return ++idCount;
    }
    void parseProc::saveJson() {
        std::ofstream output;
        output << std::setw(4) << database;
    }
    void parseProc::multiplyRecipe() {

    }



} // parse