#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
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

class precursorToken {
public:
    std::string precursorName;
    int precursorAmount = 0;
    precursorToken(std::string n, int a)    //token pair for vector storage
        :precursorName(std::move(n)), precursorAmount(a){}
};
//Token for passing args w/o more params
class findPrecursorToken {
public:
    std::string findPrecursorName;
    int originalAmount;
    findPrecursorToken(std::string n, int a)
        :findPrecursorName(std::move(n)), originalAmount(a){}
};

void findNthPrecursor(int originalAmount, std::pmr::vector<precursorToken>& precursorStorage);

//Delimiter function
void stringDelimiter(const findPrecursorToken& findToken,std::pmr::vector<precursorToken>& precursorStorage) {
    std::stringstream tempSS(findToken.findPrecursorName);
    std::string tempStorage;
    int morePrecursors = 0;
    char response;
    char del = ',';
    //start delimiter
    while(std::getline(tempSS, tempStorage, del )) {
        cin.ignore(10000, '\n');
        cout<<"How many " << tempStorage << "s do you need?\n";
        cin>>morePrecursors;
        //printing test
            //cout<< morePrecursors << tempStorage;
        morePrecursors *= findToken.originalAmount;
           // cout<< morePrecursors << findToken.originalAmount;
        precursorToken Precursors(tempStorage,morePrecursors);
        precursorStorage.push_back(Precursors);
            //cout<< precursorStorage[0].precursorAmount;
        cout<<"Are there any precursors?\n";
        cin>> response;
        if (response == 'y')
            findNthPrecursor(morePrecursors,precursorStorage);
    }
}

//Find the nth precursor
void findNthPrecursor(const int originalAmount, std::pmr::vector<precursorToken>& precursorStorage) {
    cout<<"How many precursors are there?\n";
    int findPrecursorAmount = 0;
    cin>>findPrecursorAmount;
    std::string findPrecursorName;
    if(findPrecursorAmount > 1) {
        cout<< "What are there names? Insert with commas and no spaces \n";
        cin>>findPrecursorName;
        //create token with amount limiter
        findPrecursorToken findToken(findPrecursorName, originalAmount);
        //printing
        //cout<< "precursor names: " << findToken.findPrecursorName << "\nprecursor amts: " << findToken.originalAmount << "\n";
        stringDelimiter(findToken, precursorStorage);
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

//find precursors after it has been stated there are more than 1
void findFirstPrecursor(const int originalAmount, std::pmr::vector<precursorToken>& precursorStorage) {
    cout<<"How many precursors are there?\n";
    int findPrecursorAmount = 0;
    cin>>findPrecursorAmount;
    std::string findPrecursorName;
    if(findPrecursorAmount > 1) {
        cout<< "What are there names? Insert with commas and no spaces \n";
        cin>>findPrecursorName;
        //create token with amount limiter
        findPrecursorToken findToken(findPrecursorName, originalAmount);
        //printing
            //cout<< "precursor names: " << findToken.findPrecursorName << "\nprecursor amts: " << findToken.originalAmount << "\n";
        stringDelimiter(findToken, precursorStorage);
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
    std::pmr::vector<precursorToken> precursorStorage;
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
    if (precursor == 'y') {
        //call Precursor functions and store in vector
        findFirstPrecursor(originalAmount, precursorStorage);
        //Print all recipes
        for (const auto& token : precursorStorage) {
            cout << "You need "<< token.precursorAmount << " " << token.precursorName << "\n";
        }
    }
    else {
        cout<<"No precursors? Just make " <<originalAmount << " " << originalCraft << "(s)\n";
    }
}