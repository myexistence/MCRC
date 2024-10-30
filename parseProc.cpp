//
// Created by Coding on 10/29/24.
//

#include <iostream>
#include "parseProc.h"

#include <random>
#include <sstream>
#include <__random/random_device.h>

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

    //Given a name, find a matching ID
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

    //When a precursor doesn't exist, create an ID and precursor object
    nlohmann::json parseProc::createPrecursorInput(const std::pmr::vector<precursor::precursorToken>& precursors,
        nlohmann::json& precursorArray) {
        for (const auto& it: precursors) {
            precursorArray.push_back({
                {"amount", it.precursorAmount},
                {"id", nextJsonID()}
            });
        }
        return precursorArray;
    }

    //Turn a comma seperated list of precrusors into a vector
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

    //Take in original precursors & turn them into tokens,
    //Sends tokens to be turned into arrays, then sends them to be turned into a recipe
    void parseProc::recipeParser(std::pmr::vector<std::string>& originalPrecursorVector,
        const std::string& originalName) {
        std::pmr::vector<precursor::precursorToken> precursorVector;
        nlohmann::json createArray = nlohmann::json::array();
        for (const auto& precursor_it: originalPrecursorVector) {
            cout<<"How many "<<  precursor_it << " do you need?" <<std::endl;
            int amountNeeded; cin >> amountNeeded;
            precursor::precursorToken toAdd(precursor_it,amountNeeded);
            if(!checkJsonNameExists(precursor_it)) {
                precursorVector.push_back(toAdd);
            }else
                toAppend(precursor_it,createArray,amountNeeded);
        }
        createPrecursorInput(precursorVector,createArray);
        addNewRecipe(originalName,createArray);
        cout<< std::setw(4)<<database<<std::endl;


    }

    //If a precursor already exists, find the ID given a name and create the object
    nlohmann::json parseProc::toAppend(const std::string& precursorName, nlohmann::json& precursors, const int& amount) {
        int id = matchID(precursorName);
        precursors.push_back({
        {"amount", amount},
        {"id",id}
        });
        return precursors;
    }

    //Create an entire recipe
    void parseProc::addNewRecipe(const std::string& parent, nlohmann::json& precursors) {
        auto nextID = nextJsonID();
        database["recipes"].push_back({
        {"amount", 1 /*parent.yield create yield member in precursorToken*/},
        {"id", nextID},
        {"name", parent},
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
        int min = 0;
        int max = 100000;
        std::random_device toSeed;
        std::mt19937 seed(toSeed());
        std::uniform_int_distribution<> rng(min,max);
        int newID = rng(seed);
        if(!idExists(newID))
            return newID;
        newID = nextJsonID();
        return newID;
    }

    bool parseProc::idExists(const int &id) {
        for (const auto& it : database["baseItems"])
            if(it["id"] == id)
                return  true;
        for (const auto& it : database["recipes"])
            if(it["id"] == id)
                return  true;
        return false;
    }
    void parseProc::saveJson() {
        std::ofstream output("../recipes.json");
        output << std::setw(4) << database;
    }

    //Turn a map of
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

    //Take an ID and matches it to a name that exist in the DB
    std::string parseProc::idNameMatch(const int& id) {
        for (const auto& it : database["baseItems"])
            if(it["id"] == id)
                return  it["name"];
        for (const auto& it : database["recipes"])
            if(it["id"] == id)
                return  it["name"];
            std::cerr << "ERROR: "<< id << " exists but has no matching name" << std::endl << "EXITING" << std::endl;

    }

    //Takes a token and checks to see if it already exists in the vector then adds the two together
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

    //Recursive: Takes a recipe and multiplies its precursors by it
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