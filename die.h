#ifndef DIE_H
#define DIE_H
#include <iomanip>

class Die {
 public:
    Die();
    Die(int newSides);
    int getSides();
    int getFace();
    void setSides(int newSides);
    int roll();

 private:
    int sides;
    int face;
};
#endif