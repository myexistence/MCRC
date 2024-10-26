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
    precursorToken(std::string n, int a)
        :precursorName(std::move(n)), precursorAmount(a){}
};
//HUHH???

precursorToken findPrecursor(int x) { //find precursors after it has been stated there are more than 1
    int findPrecursorMultiple = x;
    cout<<"How many precursors are there?\n";
    int findPrecursorAmount = 0;
    cin>>findPrecursorAmount;
    std::string findPrecursorName;
    if(findPrecursorAmount > 1) {
        //loop through amount of precursors and give them names
        for (int i = 0; i < findPrecursorAmount; ++i) {
            cout<< "Name one precursor" << std::endl;
            std::getline(cin >> std::ws, findPrecursorName);
/* The simplest start is by just outputting each precurssor as it is found */

        }
    }
    else { //case for only one precurssor
        cout<< "What is it?\n";
        std::string findOnePrecursorName;
        std::getline(cin >> std::ws, findOnePrecursorName);
        //cin.ignore(0,'\n');
        int precursorAmountNeeded = 0;
        cout<< "And how many?\n";
        cin>> precursorAmountNeeded;
        return {findOnePrecursorName, precursorAmountNeeded};
    }
}
int main() {
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
        //call Precursor function and use token to grab return token
        precursorToken final = findPrecursor(originalAmount);
        int finalNum = final.precursorAmount;
        std::string finalName = final.precursorName;
        cout<<"To make "<< originalAmount << " " << originalCraft << "s\n";
        cout<< "You need " << finalNum * originalAmount << " " << finalName << "s";
    }
    else
        cout<<"No precursors? Just make " <<originalAmount << " " << originalCraft << "(s)\n";
}