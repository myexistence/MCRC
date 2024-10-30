#include <iostream>
#include <utility>
#include <sstream>
#include <__algorithm/ranges_find.h>
#include <__algorithm/ranges_sort.h>

#include <json.hpp>
#include "parseProc.h"

using precursor::precursorToken;
using std::cout;
using std::cin;

int main() {
    while (true) {
        while(true) {
            parse::parseProc parser("../recipes.json");

            cout<<"What would you like to craft? (use \"_\" for spaces)" << std::endl;
            std::string originalRecipe;
            cin >> originalRecipe;

            //Recipe in database - multiply and output
            if(parser.checkJsonNameExists(originalRecipe) == true) {
                cout<< "Found "<< originalRecipe << "!" << std::endl;

                cout<< "How many "<< originalRecipe <<" would you like to craft?"<<std::endl;
                int originalAmount;
                cin >> originalAmount;

                std::pmr::vector<precursorToken> readyPrecursors;
                parser.multiplyRecipe(originalRecipe,originalAmount,readyPrecursors);
                cout<< "To make " << originalAmount <<" " << originalRecipe<< "(s) you need: "<<std::endl;
                for (const auto& it : readyPrecursors)
                    cout << it.precursorAmount << " " << it.precursorName << std::endl;
                break;
            }
            //Create recipe
            std::cout << "Does it have any precursors? ('Y' or 'N')"<<std::endl;
            char originalPrecursorsResponse;
            cin >> originalPrecursorsResponse;

            if (originalPrecursorsResponse == 'y') {
                cout<<"List precursors. (Use a ',' for seperation and '_' for spaces)"<<std::endl;
                std::string originalPrecursors;
                cin >> originalPrecursors;
                std::pmr::vector<std::string> originalPrecursorVector = parser.stringDelimiter(originalPrecursors);
                parser.recipeParser(originalPrecursorVector,originalRecipe);
                cout << "All precursors have been added" <<std::endl;
                break;

            }
            if (originalPrecursorsResponse == 'n') {
                parser.addBaseItem(originalRecipe);
                parser.saveJson();
                break;
            }
        }
        char cont;
        cout<<"Continue? ('Y' or 'N')" << std::endl;
        cin>> cont;
        if (cont == 'n')
            break;
    }
    return 0;
}