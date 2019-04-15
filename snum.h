#ifndef SNUM_H
#define SNUM_H
#include <string>
#include <iostream>
#include "Range.h"

using namespace std;

// 是否有符号数
enum SYMBOL {SIGNED, UNSINGED};
// 运算后取整方式，四舍五入还是截取
enum FLOORTYPE {ROUND, TRUNC};

class snum {
private:
    void printDouble(double x);
    double cutByPercision(double num);

public:
    double real;        // 实部
    double imag;        // 虚部
    SYMBOL symbol;      // 符号
    int total;          // 总位数
    int frac;           // 小数点后有几位
    FLOORTYPE floortype;         // 是否四舍五入
	bool hasPercision = false;

    snum() {}
    snum(double real, double imag) {
        this->real =real;
        this->imag = imag;
        this->symbol = SIGNED;
        this->total = 0;
        this->frac = 0;
        this->floortype = ROUND;
		this->hasPercision = false;
    }

    snum(double real, double imag, SYMBOL symbol, int total, int frac) {
        this->real =real;
        this->imag = imag;
        this->symbol = symbol;
        this->total = total;
        this->frac = frac;
        this->floortype = TRUNC;
		this->hasPercision = true;
    }

    void setPercision(SYMBOL symbol, int total, int frac, FLOORTYPE floortype);

    snum operator=(const snum& x);
    snum operator+(const snum& x);
    snum operator-(const snum& x);
    snum operator*(const snum& x);
    // 从double赋值
    snum operator=(double x);

    void print();

    static snum* buildArray(int n, SYMBOL symbol, int total, int frac, FLOORTYPE floortype);
    static void fillPersision(snum arr[], int len, SYMBOL symbol, int total, int frac, FLOORTYPE floortype);
};
#endif //SNUM_H
