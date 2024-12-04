/**
 *        @file: monopoly.cc
 *      @author: Kyle Carey
 *        @date: December 04, 2024
 *       @brief: Add Description
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "die.h"
using namespace std;

/// function prototypes

int main(int argc, char const *argv[]) {
    Die d;
    Die c(-2);
    cout << d.getFace() << endl;
    cout << c.getFace() << endl;
    cout << d.roll() << endl;
    cout << c.roll() << endl;
    return 0;
}/// main