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
            const nlohmann::json& getDatabase() {
                return database;
            };
            void addBaseItem(const std::string& name);

            nlohmann::json toAppend(const std::string& precursorName, nlohmann::json& precursors, const int& amount);

            int matchID (const std::string& nameMatch);


            nlohmann::json createPrecursorInput(const std::pmr::vector<precursor::precursorToken>& precursors);

            void addNewRecipe(precursor::precursorToken& parent,
                nlohmann::json& precursors);

            bool checkJsonNameExists(const std::string& name);

            int nextJsonID();

            void saveJson();

            bool checkBasicItems(const std::string& name);

            bool checkRecipes(const std::string& name);

            std::pmr::map<int,int> findPrecursors(const std::string& recipeName);


            void multiplyRecipe(const std::string& recipeName, const int& amount);
        };



} // parse
#endif //PARSEPROC_H
