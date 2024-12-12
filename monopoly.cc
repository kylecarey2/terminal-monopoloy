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
#include <cctype>
#include "die.h"
#include "property.h"
#include "player.h"
#include "board.h"
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
void confirmPlayers(const vector<Player> &players); // prompts user to confirm players playing the game
void cyclePlayers(vector<Player> &players); // cycles the players
void cyclePlayers(vector<Player> &players, const int &randNum); // cycles the players a specified amount of times
void quitGame(); // quits the game
void showActions(); // shows the actions



const string FILENAME = "prop.txt";
const int MAX_PLAYERS = 6;
const int MAX_NAME_LENGTH = 15; // play with this number to find ideal length

int main(int argc, char const *argv[]) {
    /// Create variables / objects associated with the game
    vector<Property> properties;
    vector<Player> players;
    Die D1, D2;

    /// Show welcome message with instructions

    /// Load properties and players into vectors and create board
    loadProperties(properties);
    createPlayers(players);
    confirmPlayers(players);
    Board board(&properties, &players);
    cout << "Starting game..." << endl;


    cout << endl;
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

    // Make sure there's 40 properties needed to fill the board
    if (properties.size() != 40) {
        cout << "Error: \"" << FILENAME << "\" must have 40 properties" << endl;
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

void confirmPlayers(const vector<Player> &players) {
    cout << "Confirm the following players are playing:" << endl;
    for (size_t i = 0; i < players.size(); i++) {
        cout << " -" << players.at(i).getName() << endl;
    }
    cout << endl;
    cout << "Is this correct? (y/n): ";
    string response;
    cin >> response;
    if (tolower(response.at(0)) != 'y') {
        cout << "Players not confirmed. Terminating program" << endl;
        exit(0);
    }
}

void quitGame() {
    string response;
    do {
        cout << "All progress will be lost. Confirm you wish to quit the game. (y/n): ";
        cin >> response;

        if (tolower(response.at(0)) == 'y') {
            cout << "Quitting the game" << endl;
            exit(0);
        }
        else if (tolower(response.at(0)) == 'n') {
            cout << "The game will continue" << endl;
            break;
        }
    } while(response.at(0) != 'y' || response.at(0) != 'n');
}

void showActions() {
    cout << "Here are the following actions:" << endl;
    cout << "r - roll the dice, u - upgrade current property, h - show actions, q - quit the game" << endl; // add change identifier and save game once we get there
}

void cyclePlayers(vector<Player> &players) {
    players.push_back(players.at(0));
    players.erase(players.begin());
}

void cyclePlayers(vector<Player> &players, const int &randNum) {
    for (int i = 0; i < randNum; i++) {
        cyclePlayers(players);
    }
}

