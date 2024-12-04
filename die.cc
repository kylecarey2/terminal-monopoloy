#include "die.h"

#include <cstdlib>
using namespace std;

Die::Die() {
    srand(time(nullptr));
    sides = 6;
    face = rand() % sides + 1;
}

Die::Die(int newSides) {
    srand(time(nullptr));
    if (newSides > 1) {
        sides = newSides;
        face = rand() % sides + 1;
    }
    else {
        sides = 6;
        face = rand() % sides + 1;
    }
}

int Die::getSides() {
    return sides;
}

int Die::getFace() {
    return face;
}

void Die::setSides(int newSides) {
    if (newSides > 1) {
        sides = newSides;
        face = rand() % sides + 1;
    }
}

int Die::roll() {
    face = rand() % sides + 1;
    return face;
}