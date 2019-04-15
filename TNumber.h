#ifndef SNUM_TNUMBER_H
#define SNUM_TNUMBER_H

#include <iostream>
using namespace std;

class TNumber {

public:
    double num;

    TNumber(double num) {
        this->num = num;
    }

    TNumber operator+(const TNumber& x) {
        int result = x.num + this->num;
        return TNumber(result);
    }

    void print() {
        cout << this->num << endl;
    }

};


#endif //SNUM_TNUMBER_H
