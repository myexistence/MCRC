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

            void amendRecipe(const std::string& recipe, int);

            int matchID (const std::string& nameMatch);


            nlohmann::json createPrecursorInput(const std::pmr::vector<precursor::precursorToken>& precursors);

            void addRecipe(precursor::precursorToken& parent,
                const std::pmr::vector<precursor::precursorToken>& precursors);

            bool checkJsonNameExists(const std::string& name);

            int nextJsonID();

            void saveJson();

            void multiplyRecipe();
        };



} // parse
#endif //PARSEPROC_H
