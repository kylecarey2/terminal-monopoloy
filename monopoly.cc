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
#include "player.h"
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
void loadProperties(vector<Property> &properties); // loads the properties from file into a vector of properties
void createPlayers(vector<Player> &players); // prompts user for player number then their names


const string FILENAME = "properties.txt";
const int MAX_PLAYERS = 8;
const int MAX_NAME_LENGTH = 15; // play with this number to find ideal length

int main(int argc, char const *argv[]) {
    // Player one;
    // Player two(3);
    // Player three(2, "Test");
    // cout << one.getId() << " " << one.getName() << " " << one.getBalance() << endl;
    // cout << two.getId() << " " << two.getName() << " " << two.getBalance() << endl;
    // cout << three.getId() << " " << three.getName() << " " << three.getBalance() << endl;
    // three.addBalance(200);
    // cout << three.getId() << " " << three.getName() << " " << three.getBalance() << endl;


    
    // vector<Property> properties;
    // loadProperties(properties);
    // for (size_t i = 0; i < properties.size(); i++) {
    //     cout << properties[i].getId() << "\t";
    //     cout << properties[i].getName() << "\t";
    //     cout << properties[i].getPrice() << "\t";
    //     cout << properties[i].getColor() << endl;
    // }

    vector<Player> players;
    createPlayers(players);
    for (size_t i = 0; i < players.size(); i++) {
        cout << players[i].getId() << "\t";
        cout << players[i].getName() << "\t";
        cout << players[i].getBalance() << "\n";
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

void createPlayers(vector<Player> &players) {
    /// Prompt user for number of players
    int numPlayers;
    cout << "Enter the number of players (2-" << MAX_PLAYERS << "): ";
    cin >> numPlayers;
    if (cin.fail() || numPlayers < 2 || numPlayers > MAX_PLAYERS) {
        cout << "Error: enter an integer between 2-" << MAX_PLAYERS << endl;
        exit(0);
    } 

    /// Create new players
    cout << "Names must be below " << MAX_NAME_LENGTH << " characters" << endl;
    for (int i = 0; i < numPlayers; i++) {
        /// Prompt for player's name
        string name;
        cout << "                                   ";
        for (int i = 0; i < MAX_NAME_LENGTH; i++) { cout << "_"; }
        cout << "\r";
        cout << "Please enter the name of player " << i + 1 << ": ";
        
        /// Read in and verify name
        cin >> name;
        if (cin.fail() || name.length() > MAX_NAME_LENGTH) {
            cout << "Error: enter a string between 1-" << MAX_NAME_LENGTH << " characters" << endl;
            exit(0);
        }

        /// Create Player and add to vector
        Player p(i, name);
        players.push_back(p);
    }

    cout << endl;
}
