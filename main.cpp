#include <iostream>
#include <time.h>
#include "snum.h"
#include "sfile.h"

int main() {

    snum a, b, c;
    a.setPercision(SIGNED, 10, 4, ROUND);
    a = 3.231;
    a.print();cout << endl;
	b.setPercision(SIGNED, 12, 5, TRUNC);
    b = 2.4533;
    b.print(); cout << endl;
    c.setPercision(SIGNED, 12, 2, ROUND);
    c = a + b;
	c.print(); cout << endl;

    snum *x = snum::buildArray(100, SIGNED, 10, 2, ROUND);
    snum y[100];
    snum::fillPersision(y, 100, SIGNED, 10, 2, ROUND);
    
	sfile input;
	input.filename = "data.txt";
	input.runMode = DEBUG;
	input.init();
	for (int i = 0; i < 3; i++) {
		sdata line = input.readLine();
		cout << "a="; line.a.print();
		cout << ",b="; line.b.print();
		cout << ",c="; line.c.print();
		cout << ",d=" << line.d;
		cout << ",e=" << line.e << endl;
	}

	getchar();
    return 0;
}