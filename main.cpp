#include <iostream>
#include <utility>
#include <vector>
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
    //token vector
    precursorToken(std::string n, int a)
        :precursorName(std::move(n)), precursorAmount(a){}
};


//find precursors after it has been stated there are more than 1
void findFirstPrecursor(std::pmr::vector<precursorToken>& precursorTracking) {
    cout<<"How many precursors are there?\n";
    int findPrecursorAmount = 0;
    cin>>findPrecursorAmount;
    std::string findPrecursorName;
    if(findPrecursorAmount > 1) {
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
        precursorTracking.push_back(toInput);
    }

}

std::vector<precursorToken> findNthPrecursor() {

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