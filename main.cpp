#include <iostream>
#include "TNumber.h"
#include "snum.h"
#include <time.h>

int main() {

    snum a, b, c;
    a.setPercision(SIGNED, 10, 4, ROUND);
    a = 3.231;
    a.print();
    b = 2.4533;
    b.setPercision(SIGNED, 12, 5, TRUNC);
    b.print();
    c.setPercision(SIGNED, 12, 2, ROUND);
    c = a + b;
    c.print();

    snum *x = snum::buildArray(100, SIGNED, 10, 2, ROUND);
    snum y[100];
    snum::fillPersision(y, 100, SIGNED, 10, 2, ROUND);

    return 0;
}