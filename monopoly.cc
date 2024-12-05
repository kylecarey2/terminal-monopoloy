/**
 *        @file: monopoly.cc
 *      @author: Kyle Carey
 *        @date: December 04, 2024
 *       @brief: Add Description
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "die.h"
#include "property.h"
using namespace std;

/// function prototypes
/**
 * Function:    duplicateId
 *              returns if the id has already been used in other properties
 *
 * @param newId - the id, as an int
 * @return - bool, true if duplicate, false if not
 */
bool duplicateId(const int &newId, const vector<Property> properties);
void loadProperties(vector<Property> &properties);


const string FILENAME = "properties.txt";

int main(int argc, char const *argv[]) {

    vector<Property> properties;
    loadProperties(properties);
    for (size_t i = 0; i < properties.size(); i++) {
        cout << properties[i].getId() << "\t";
        cout << properties[i].getName() << "\t";
        cout << properties[i].getPrice() << "\t";
        cout << properties[i].getColor() << endl;
    }
    return 0;
}/// main

bool duplicateId(const int &newId, const vector<Property> properties) {
    for (size_t i = 0; i < properties.size() - 1; i++) {
        if (newId == properties[i].getId()) {
            return true;
        }
    }

    return false;
}  /// duplicateId

void loadProperties(vector<Property> &properties) {
    /// Create input stream
    ifstream in;
    in.open(FILENAME);
    if (in.fail()) {
        cout << "Error opening \"" << FILENAME << "\"" << endl;
        exit(0);
    }

    /// Read file content and add properties
    string propertyData;
    getline(in, propertyData); // disregard header
    while (getline(in, propertyData)) {
        Property p(propertyData);
        properties.push_back(p);

        /// Check for duplicate id's
        if (duplicateId(properties[properties.size() - 1].getId(), properties)) {
            cout << "Error: duplicate property id detected. Each id must be unique" << endl;
            exit(0);
        }
    }

    /// Make sure there's 28 properties needed to fill the board
    if (properties.size() != 28) {
        cout << "Error: \"" << FILENAME << "\" must have 27 properties" << endl;
        exit(0);
    }

    in.close();
}