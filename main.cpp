#include <iostream>
#include <time.h>
#include "snum.h"
#include "sfile.h"

int main() {

    snum a, b, c;
    a.setPercision(SIGNED, 10, 4, ROUND);
    a = 3.231;
    a.print();
	b.setPercision(SIGNED, 12, 5, TRUNC);
    b = 2.4533;
    b.print();
    c.setPercision(SIGNED, 12, 2, ROUND);
    c = a + b;
    c.print();

    snum *x = snum::buildArray(100, SIGNED, 10, 2, ROUND);
    snum y[100];
    snum::fillPersision(y, 100, SIGNED, 10, 2, ROUND);

	// 文件的使用
	sfile input;
	input.filename = "data.txt";
	input.init();
	
	getchar();
    return 0;
}