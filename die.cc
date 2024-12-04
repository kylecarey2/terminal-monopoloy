#include "die.h"

#include <cstdlib>
using namespace std;

Die::Die() {
    srand(time(nullptr)); // seed the die
    sides = 6;
    face = rand() % sides + 1;
}  /// Die

Die::Die(int newSides) {
    srand(time(nullptr)); // seed the die
    if (newSides > 1) {
        sides = newSides;
        face = rand() % sides + 1;
    }
    else {
        sides = 6;
        face = rand() % sides + 1;
    }
}  /// Die

int Die::getSides() {
    return sides;
}  /// getSides

int Die::getFace() {
    return face;
}  /// getFace

void Die::setSides(int newSides) {
    if (newSides > 1) {
        sides = newSides;
        face = rand() % sides + 1;
    }
}  /// setSides

int Die::roll() {
    face = rand() % sides + 1;
    return face;
}  /// roll