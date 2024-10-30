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


            nlohmann::json createPrecursorInput(const std::pmr::vector<precursor::precursorToken>& precursors,
                nlohmann::json& precursorArray);

            void addNewRecipe(const std::string& parent,
                nlohmann::json& precursors);

            bool checkJsonNameExists(const std::string& name);

            int nextJsonID();

            void saveJson();

            bool checkBasicItems(const std::string& name);

            bool checkRecipes(const std::string& name);

            std::pmr::map<int,int> findPrecursors(const std::string& recipeName);

            std::string idNameMatch(const int& id);

            bool vectorOutputCheck(precursor::precursorToken& precursor,
            std::pmr::vector<precursor::precursorToken>& readyPrecursors);

            std::pmr::vector<std::string> stringDelimiter(const std::string& originalPrecursors);

            void recipeParser(std::pmr::vector<std::string>& originalPrecursorVector,
                const std::string& originalName);

            void multiplyRecipe(const std::string& recipeName, int amount,
            std::pmr::vector<precursor::precursorToken>& readyPrecursors);
        };



} // parse
#endif //PARSEPROC_H
