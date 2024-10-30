//
// Created by Coding on 10/29/24.
//

#include <iostream>
#include "parseProc.h"
#include <sstream>

using std::cout;
using std::cin;

namespace parse {
    void parseProc::addBaseItem(const std::string& name) {
        auto id = nextJsonID();
        database["baseItems"].push_back({
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

    std::pmr::vector<std::string> parseProc::stringDelimiter(const std::string& originalPrecursors) {
        std::stringstream tempSS(originalPrecursors);
        std::string tempStorage;
        char del = ',';
        std::pmr::vector<std::string> originalPrecursorVector;
        //start delimiter
        while(std::getline(tempSS, tempStorage, del )) {
            originalPrecursorVector.push_back(tempStorage);

        }
        return originalPrecursorVector;
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
        for (const auto& it: database["baseItems"])
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
        idCount += database["baseItems"].size();
        idCount += database["recipes"].size();
        return ++idCount;
    }
    void parseProc::saveJson() {
        std::ofstream output("../recipes.json");
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

    std::string parseProc::idNameMatch(const int& id) {
        for (const auto& it : database["baseItems"])
            if(it["id"] == id)
                return  it["name"];
        for (const auto& it : database["recipes"])
            if(it["id"] == id)
                return  it["name"];
            std::cerr << "ERROR: "<< id << " exists but has no matching name" << std::endl << "EXITING" << std::endl;

    }

    bool parseProc::vectorOutputCheck(precursor::precursorToken& precursor,
        std::pmr::vector<precursor::precursorToken>& readyPrecursors) {
        if(auto searchVector
            = std::find(readyPrecursors.begin(), readyPrecursors.end(), precursor);
            searchVector != readyPrecursors.end())
        {
            searchVector->precursorAmount += precursor.precursorAmount;
            return true;
        }
        return false;
    }

    void parseProc::multiplyRecipe
    (const std::string& recipeName, int amount,std::pmr::vector<precursor::precursorToken>& readyPrecursors) {
        std::pmr::map<int,int> rawPrecursors = findPrecursors(recipeName);
        std::pmr::vector<precursor::precursorToken> loopBreaker;
        for (auto& it : rawPrecursors) {
            std::string newName = idNameMatch(it.first);
            int newAmount = (amount * it.second);
            precursor::precursorToken toAdd(newName,newAmount);
            if(!vectorOutputCheck(toAdd,readyPrecursors))
                readyPrecursors.push_back(toAdd);
            loopBreaker.push_back(toAdd);
        }
        for (auto& it2: loopBreaker) {
            if(checkRecipes(it2.precursorName)) {
                multiplyRecipe(it2.precursorName,it2.precursorAmount,readyPrecursors);
            }
        }
    }



} // parse