#ifndef SNUM_RANGE_H
#define SNUM_RANGE_H

#include <cmath>
#include <map>
using namespace std;

class Range {
public:
    static long SIGNED_MAX[33];
    static long SIGNED_MIN[33];
    static long UNSIGNED_MAX[33];
    static double POW_2[33];

    static double powl(int x) {
        return pow(2, x);
    }
    static long umax(int x) {
        return static_cast<long>(pow(2,x)) - 1;
    }

    static long smax(int x) {
        return static_cast<long>(pow(2, x - 1) - 1);
    }

    static long smin(int x) {
        return static_cast<long>(-1 * pow(2, x - 1)) + 1;
    }
};
#endif //SNUM_RANGE_H
