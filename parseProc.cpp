//
// Created by Coding on 10/29/24.
//

#include <iostream>
#include "parseProc.h"

using std::cout;
using std::cin;

namespace parse {
    void addBaseItem(std::string name, parseProc& database) {

    }
    void amendRecipe(std::string recipe, int, parseProc database) {

    }
    void addRecipe(precursor::precursorToken& parent,
                    std::pmr::vector<precursor::precursorToken> precursorStorage,
                    parseProc& database) {

    }
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