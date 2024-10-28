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
/* Grammar
 * Sequence
 *  String "," String
 *  Number "," Number
 * Number
 *  "int"
 * String
 *  "string"
 */

//Token for passing args w/o more params
class findPrecursorToken {
public:
    std::string findPrecursorName;
    int originalAmount;
    findPrecursorToken(std::string n, int a)
        :findPrecursorName(std::move(n)), originalAmount(a){}
};

void findNthPrecursor(std::string & parentRecipe,int originalAmount, std::pmr::vector<precursorToken>& precursorStorage);
//Look through vector for pre-existing precursors
//We need: the current vector, the precursor in question, amount needed. If the precursor in question exists, modify on iterator, else create new
bool existsCheck(const precursorToken& Precursors, std::pmr::vector<precursorToken>& precursorStorage) {
    if(auto searchVector
        = std::ranges::find(precursorStorage.begin(), precursorStorage.end(), Precursors);
        searchVector != precursorStorage.end())
    {
        searchVector->precursorAmount += Precursors.precursorAmount;
        return true;
}
    return false;
}
//Delimiter function
void stringDelimiter(std::string& parentRecipe, const findPrecursorToken& findToken,std::pmr::vector<precursorToken>& precursorStorage) {
    std::stringstream tempSS(findToken.findPrecursorName);
    std::string tempStorage;
    int morePrecursors = 0;
    char response;
    char del = ',';
    //start delimiter
    while(std::getline(tempSS, tempStorage, del )) {
        std::string newParent = tempStorage;
        cin.ignore(10000, '\n');
        cout<<"How many " << tempStorage << "s do you need?\n";
        cin>>morePrecursors;
            morePrecursors *= findToken.originalAmount;
           // cout<< morePrecursors << findToken.originalAmount;
        if (precursorToken Precursors(tempStorage,morePrecursors); existsCheck(Precursors, precursorStorage) == false)
            precursorStorage.push_back(Precursors);
        cout<<"Are there any precursors?\n";
        cin>> response;
        if (response == 'y') {
            findNthPrecursor(newParent, morePrecursors,precursorStorage);
            cout<< "Back in "<< parentRecipe << ". \n";
        }
    }
}
//Find the nth precursor
void findNthPrecursor(std::string & parentRecipe,const int originalAmount, std::pmr::vector<precursorToken>& precursorStorage) {
    cout<<"How many precursors are there?\n";
    int findPrecursorAmount = 0;
    cin>>findPrecursorAmount;
    if(std::string findPrecursorName; findPrecursorAmount > 1) {
        cout<< "What are there names? Insert with commas and no spaces \n";
        cin>>findPrecursorName;
        //create token with amount limiter
        findPrecursorToken findToken(findPrecursorName, originalAmount);
        //printing
        //cout<< "precursor names: " << findToken.findPrecursorName << "\nprecursor amts: " << findToken.originalAmount << "\n";
        stringDelimiter(parentRecipe, findToken, precursorStorage);
    }
    else {
        cout<< "What is it?\n";
        std::string findOnePrecursorName;
        std::getline(cin >> std::ws, findOnePrecursorName);
        //cin.ignore(0,'\n');
        int precursorAmountNeeded = 0;
        cin.ignore(10000, '\n');
        cout<< "And how many?\n";
        cin>> precursorAmountNeeded;
        precursorToken toInput(findOnePrecursorName, (precursorAmountNeeded * originalAmount));
        precursorStorage.push_back(toInput);
    }
}
int main() {
    cout<<"What do you want to craft? \n";
    std::string originalCraft;
    std::getline(cin >> std::ws, originalCraft);
    //cin.ignore(10000, '\n');
    cout<<"How many?\n";
    int originalAmount;
    cin>> originalAmount;
    cout<<"Any precursors? Y or N.\n";
    char precursor;
    cin>> precursor;
    //check for precursor
    if (std::pmr::vector<precursorToken> precursorStorage;precursor == 'y') {
        //call Precursor functions and store in vector
        findNthPrecursor(originalCraft,originalAmount, precursorStorage);
        //lambda sort rule for greatest to least
        auto sortRule = [] (const precursorToken& a, const precursorToken& b) {
            return a > b;
        };
        std::sort(precursorStorage.begin(), precursorStorage.end(), sortRule);
        for (const auto& token : precursorStorage) {
            cout << "You need "<< token.precursorAmount << " " << token.precursorName << "\n";
        }
    }else cout<<"No precursors? Just make " <<originalAmount << " " << originalCraft << "(s)\n";
}