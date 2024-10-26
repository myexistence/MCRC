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
//Find the nth precursor
void findNthPrecursor(std::pmr::vector<precursorToken>& precursorStorage) {

}

//Delimiter function
void stringDelimiter(int precursorAmt, const std::string& precursorName,std::pmr::vector<precursorToken>& precursorStorage) {
    std::stringstream tempSS(precursorName);
    std::string tempStorage;
    int morePrecursors = 0;
    char response;
    char del = ' ';
    while(std::getline(tempSS, tempStorage, del )) {
        cout<<"How many " << tempStorage << "s do you need?";
        cin>>morePrecursors;
        precursorToken Precursors(tempStorage,morePrecursors);
        precursorStorage.push_back(Precursors);
        cout<<"Are there any precursors?";
        cin>> response;
        if (response == 'y')
            findNthPrecursor(precursorStorage);

    }
}

//find precursors after it has been stated there are more than 1
void findFirstPrecursor(std::pmr::vector<precursorToken>& precursorStorage) {
    cout<<"How many precursors are there?\n";
    int findPrecursorAmount = 0;
    cin>>findPrecursorAmount;
    std::string findPrecursorName;
    if(findPrecursorAmount > 1) {
        cout<< "What are there names? Insert with spaces \n";
        cin>>findPrecursorName;
        stringDelimiter(findPrecursorAmount, findPrecursorName,precursorStorage);
    }
    else {
        cout<< "What is it?\n";
        std::string findOnePrecursorName;
        std::getline(cin >> std::ws, findOnePrecursorName);
        //cin.ignore(0,'\n');
        int precursorAmountNeeded = 0;
        cout<< "And how many?\n";
        cin>> precursorAmountNeeded;
        precursorToken toInput(findOnePrecursorName, precursorAmountNeeded);
        precursorStorage.push_back(toInput);
    }

}




int main() {
    std::pmr::vector<precursorToken> precursorStorage;
    cout<<"What do you want to craft? \n";
    std::string originalCraft;
    std::getline(cin >> std::ws, originalCraft);
    cout<<"How many?\n";
    int originalAmount;
    cin>> originalAmount;
    cout<<"Any precursors? Y or N.\n";
    char precursor;
    cin>> precursor;
    //check for precursor
    if (precursor == 'y') {
        //call Precursor functions and store in vector
        findFirstPrecursor(precursorStorage);
        //Print all recipes
        for (auto token : precursorStorage) {
            cout << "You need "<< token.precursorAmount << " of " << token.precursorName;
        }
    }
    else {
        cout<<"No precursors? Just make " <<originalAmount << " " << originalCraft << "(s)\n";
    }
}