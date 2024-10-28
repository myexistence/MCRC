//
// Created by Coding on 10/29/24.
//

#ifndef PRECURSORTOKEN_H
#define PRECURSORTOKEN_H

namespace precursor {

    class precursorToken {

    public:
        std::string precursorName;
        int precursorAmount = 0;
        precursorToken(std::string n, int a)    //token pair for vector storage
            :precursorName(std::move(n)), precursorAmount(a){}
        //allows token to be found
        bool operator==(const precursorToken & compare) const {
            return precursorName == compare.precursorName;
        }
        //allows token to be sorted
        bool operator>(const precursorToken & compare) const {
            return precursorAmount > compare.precursorAmount;
        }
    };

} // precursor

#endif //PRECURSORTOKEN_H
