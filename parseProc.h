//
// Created by Coding on 10/29/24.
//

#ifndef PARSEPROC_H
#define PARSEPROC_H
#include <json.hpp>
#include <fstream>
#include <vector>
#include "precursorToken.h"
namespace parse {

    class parseProc {
            nlohmann::json database;
            std::string filename;
        public:
            explicit parseProc(std::string file)
                :filename(std::move(file)) {
                std::ifstream input(filename);
                input >> database;
            }
            void addBaseItem(std::string name);

            void amendRecipe(std::string recipe, int);

            void addRecipe(precursor::precursorToken& parent,
                            std::pmr::vector<precursor::precursorToken> precursorStorage);

            bool checkJsonNameExists(std::string& name);

            int nextJsonID();

            void saveJson();

            void multiplyRecipe();
        };



} // parse
#endif //PARSEPROC_H
