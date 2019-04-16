#include "snum.h"
snum::snum(){}
snum snum::operator=(double x) {
	this->real = cutByPercision(x);
	this->intReal = (int)(this->real * Range::POW_2[this->frac]);
	this->intImag = 0;
	this->imag = 0;
    return *this;
}
snum snum::operator=(const snum& x) {
    this->real = cutByPercision(x.real);
    this->imag = cutByPercision(x.imag);
	this->intReal = (int)(this->real * Range::POW_2[this->frac]);
	this->intImag = (int)(this->imag * Range::POW_2[this->frac]);
    return *this;
}
double snum::cutByPercision(double num) {
    long inteNoFrac;
    switch (this->floortype) {
        case TRUNC:
            inteNoFrac = (long)(num * Range::POW_2[this->frac]);
            break;
        case ROUND:
            long numNoFrac = (long)(num * Range::POW_2[this->frac + 1]);
            inteNoFrac = (numNoFrac + ((numNoFrac & 0x1) << 1)) >> 1;
            break;
    }
    int inteLen = this->total - (symbol == SIGNED ? 1 : 0);

    switch (this->symbol) {
        case UNSINGED:
            if (inteNoFrac > Range::UNSIGNED_MAX[inteLen]) {
                return Range::UNSIGNED_MAX[inteLen];
            }
            break;
        case SIGNED:
        default:
            if (inteNoFrac > Range::SIGNED_MAX[inteLen]) {
                return Range::SIGNED_MAX[inteLen];
            }
            if (inteNoFrac < Range::SIGNED_MIN[inteLen]) {
                return Range::SIGNED_MIN[inteLen];
            }
            break;
    }
    return inteNoFrac / Range::POW_2[this->frac];
}
snum::snum(double real, double imag) {
	this->real = real;
	this->imag = imag;
	this->symbol = SIGNED;
	this->total = 0;
	this->frac = 0;
	this->floortype = ROUND;
	this->hasPercision = false;
	this->intReal = (int)(this->real * Range::POW_2[this->frac]);
	this->intImag = (int)(this->imag * Range::POW_2[this->frac]);
}

snum snum::operator+(const snum& x) {
    double real = this->real + x.real;
    double imag = this->imag + x.imag;
    return snum(real, imag);
}
snum snum::operator-(const snum& x) {
    double real = this->real - x.real;
    double imag = this->imag - x.imag;
    return snum(real, imag);
}
snum snum::operator*(const snum& x) {
    double real = this->real * x.real - this->imag * x.imag;
    double imag = this->imag * x.real + this->real * x.imag;
    return snum(real, imag);
}
void snum::setPercision(SYMBOL symbol, int total, int frac, FLOORTYPE floortype) {
    this->symbol = symbol;
    this->total = total;
    this->frac = frac;
    this->floortype = floortype;
	this->hasPercision = true;
}
void snum::print() {
	printf("%x+%xi", this->intReal, this->intImag);
}
snum* snum::buildArray(int n, SYMBOL symbol, int total, int frac, FLOORTYPE floortype) {
    snum *array = new snum[n];
    for (int i = 0; i < n; i++) {
        array[i].setPercision(symbol, total, frac, floortype);
    }
    return array;
}
void snum::fillPersision(snum arr[], int len, SYMBOL symbol, int total, int frac, FLOORTYPE floortype) {
    for (int i = 0; i < len; i++) {
        arr[i].setPercision(symbol, total, frac, floortype);
    }
}
