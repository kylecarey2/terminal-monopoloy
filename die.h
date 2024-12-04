#ifndef DIE_H
#define DIE_H
#include <iomanip>

class Die {
 public:
    /**
     * Function:    Die
     *              default constructor, sets sides to 6 and face to a random number between 1-6
     */
    Die();

    /**
     * Function:    Die
     *              allows user to specify the sides on the die. must be greater than 1 and then sets face to random number between 1-sides
     */
    Die(int newSides);

    /**
     * Function:    getSides
     *              returns the number of sides on the die
     *
     * @return - sides, as an int
     */
    int getSides();

    /**
     * Function:    getFace
     *              returns the current face of the die
     *
     * @return - face, as an int
     */
    int getFace();

    /**
     * Function:    setSides
     *              sets the sides to a value greater than 1 and adjusts face to be within new side value
     *
     * @param newSides - the new side to set sides to, as an int
     * @return - void
     */
    void setSides(int newSides);

    /**
     * Function:    roll
     *              generates and returns a new random number within the constraints of sides
     *
     * @return - face, as an int
     */
    int roll();

 private:
    int sides;  /// sides of the die
    int face;   /// the current face of the die
};
#endif