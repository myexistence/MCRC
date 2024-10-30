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
        if(!checkJsonNameExists(nameMatch)){
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

    nlohmann::json parseProc::toAppend(const std::string& precursorName, nlohmann::json& precursors, const int& amount) {
        int id = matchID(precursorName);
        precursors.push_back({
        {"amount", amount},
        {"id",id}
        });
        return precursors;
    }

    void parseProc::addNewRecipe(precursor::precursorToken& parent, nlohmann::json& precursors) {
        auto nextID = nextJsonID();
        database["recipes"].push_back({
        {"amount", 1 /*parent.yield create yield member in precursorToken*/},
        {"id", nextID},
        {"name", parent.precursorName},
        {"precursors", precursors}});
    }

    bool parseProc::checkBasicItems(const std::string& name) {
        for (const auto& it: database["basicItems"])
            if(it["name"] == name)
                return true;
        return false;
    }

    bool parseProc::checkRecipes(const std::string& name) {
        for(const auto& it : database["recipes"])
            if(it["name"] == name)
                return true;
        return false;
    }

    bool parseProc::checkJsonNameExists(const std::string& name) {
        if (!checkBasicItems(name) && !checkRecipes(name))
            return false;
        return true;
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

    std::pmr::map<int,int> parseProc::findPrecursors(const std::string& recipeName) {
        std::pmr::map<int,int> rawPrecursors;
        for(auto it : database["recipes"]) {
            if (it["name"] == recipeName)
                for(auto it2: it["precursors"])
                    rawPrecursors.insert({
                        it2["id"].get<int>(),
                        it2["amount"].get<int>()
                    });
        }
        return rawPrecursors;
    }

    std::pmr::vector<precursor::precursorToken> parseProc::multiplyRecipe
    (const std::string& recipeName, int amount,std::pmr::vector<precursor::precursorToken>& readyPrecursors)
    {
        std::pmr::map<int,int> rawPrecursors = findPrecursors(recipeName);
        for (auto& it : rawPrecursors) {
            std::string newName = idNameMatch(it.first);
            int newAmount = (amount * it.second);
            precursor::precursorToken toAdd(newName,newAmount);
            readyPrecursors.push_back(toAdd);
            }
        for (auto it& : readyPrecursors) {
            if(!checkBasicItems(it.precursorName) && checkRecipes(it.precursorName)) {
                multiplyRecipe(it.precursorName,it.precursorAmount,readyPrecursors);
            }
        }
        return readyPrecursors;
    }



} // parse