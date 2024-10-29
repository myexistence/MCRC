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
    void parseProc::amendRecipe(const std::string& recipe, int) {

    }
    void parseProc::addRecipe(precursor::precursorToken& parent,
                    const std::pmr::vector<precursor::precursorToken>& precursorStorage){};

    bool parseProc::checkJsonNameExists(std::string& name) {
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
    void multiplyRecipe();


} // parse