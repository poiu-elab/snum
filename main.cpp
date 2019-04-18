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
	
	// 文件的使用
	sfile input;
	input.filename = "data.txt";
	input.runMode = DEBUG;
	input.init();
	for (int i = 0; i < 3; i++) {
		//sdata line = input.readLine();
		double* line = input.readLine(5);
		for (int j = 0; j < 5; j++) {
			cout << *(line + j) << " ";
		}
		cout << endl;
	}
	
	getchar();
    return 0;
}