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
#include <chrono>
#include <thread>
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
bool duplicateId(const int &newId, const vector<Property> &properties);
void loadProperties(vector<Property> &properties); // loads the properties from file into a vector of properties
void createPlayers(vector<Player> &players); // prompts user for player number then their names
void confirmPlayers(const vector<Player> &players); // prompts user to confirm players playing the game
void cyclePlayers(vector<Player> &players); // cycles the players
void cyclePlayers(vector<Player> &players, const int &randNum); // cycles the players a specified amount of times
bool verifyQuit(); // quits the game
string showActions(); // shows the actions
string showOptions(); // shows the options
char getAction(); // prompts and gets actions
char getOption(); // prompts and gets options
void pay(Player &p1, Player &p2, const int &amount);
// string upgradeProperty(const Player* player, const int &id);
/// need a sort by id function for properties



const string FILENAME = "prop.txt";
const int MAX_PLAYERS = 8;
const int MAX_NAME_LENGTH = 15; // play with this number to find ideal length
/// First row is railroad progression, everything else is in order 
const vector<vector<int>> propRentProgression = {{25, 50, 100, 200},                    
                                                {2, 10, 30, 90, 160, 250}, 
                                                {4, 20, 60, 180, 320, 450}, 
                                                {6, 30, 90, 270, 400, 550}, 
                                                {6, 30, 90, 270, 400, 550}, 
                                                {8, 40, 100, 300, 450, 600},
                                                {10, 50, 150, 450, 625, 750},
                                                {10, 50, 150, 450, 625, 750},
                                                {12, 60, 180, 500, 700, 900},
                                                {14, 70, 200, 550, 750, 950},
                                                {14, 70, 200, 550, 750, 950},
                                                {16, 80, 220, 600, 800, 1000},
                                                {18, 90, 250, 700, 875, 1050},
                                                {18, 90, 250, 700, 875, 1050},
                                                {20, 100, 300, 750, 925, 1100},
                                                {22, 110, 330, 800, 975, 1150},
                                                {22, 110, 330, 800, 975, 1150},
                                                {24, 120, 360, 850, 1025, 1200},
                                                {26, 130, 390, 900, 1100, 1275},
                                                {26, 130, 390, 900, 1100, 1275},
                                                {28, 150, 450, 1000, 1200, 1400},
                                                {35, 175, 500, 1100, 1300, 1500},
                                                {50, 200, 600, 1400, 1700, 2000}};

int main(int argc, char const *argv[]) {
    /// Create variables / objects associated with the game
    vector<Property> properties;
    vector<Player> players;
    Die D1, D2;

    string s;
    /// Show welcome message with instructions

    /// Load properties and players into vectors and create board
    loadProperties(properties);
    createPlayers(players);
    // confirmPlayers(players);
    Board board(&properties, &players);
    sortById(properties);
    setRentProgression(properties, propRentProgression);
    // cout << "---" << endl;
    // for (size_t i = 0; i < properties.size(); i++) {
    //     Property p = properties.at(i);
    //     // cout << p.getUpgradeCount();
    //     cout << p.getRent();
    //     cout << p.getName() << " " << p.getRent() << "    ";
    //     for (size_t j = 0; j < p.getRP().size(); j++) {
    //         cout << " " << p.getRP().at(j);
    //     }
    //     cout << "\n";
    // }
    cout << "\033[2J\033[H"; 
    // players[0].setJail(false);
    players[0].addProperty(&properties[6]);
    properties[6].setOwnerId(0);
    players[0].addProperty(&properties[8]);
    properties[8].setOwnerId(0);
    players[0].addProperty(&properties[9]);
    properties[9].setOwnerId(0);
    players[1].addProperty(&properties[1]);
    properties[1].setOwnerId(1);
    players[1].addProperty(&properties[3]);
    properties[3].setOwnerId(1);
    players[1].addProperty(&properties[25]);
    properties[25].setOwnerId(1);

    // players[0].setPosition(6);
    players[1].setPosition(3);

    players[0].incrementJailCards();
    players[0].setJail(true);

    /// Game loop
    bool play = true;
    char action;
    bool doOption;
    string prevMessage; // message saying what happened with the previous action / option
    do {
        doOption = false;
        prevMessage = "";
        board.displayOverview();
        action = getAction();
        // cout << "-" << action << endl;
        if (action == 'q') {
            play = !verifyQuit();
            if (!play) {
                prevMessage = "Quit the game.";
            }
        }
        else if (action == 'r') {
            Player* p = &players.at(0);
            int spaces = 0;
            bool fromJail = false;
            
            if (p->isJailed()) {
                string response;
                if (p->getJailCards() > 0) {
                    char responseChar;
                    do {
                        cout << "Would you like to use a get out of jail free card? (y/n): ";
                        cin >> response;
                        responseChar = tolower(response.at(0));
                    } while (responseChar != 'y' && responseChar != 'n'); 

                    if (responseChar == 'y') {
                        cout << "Rolling...\n";
                        p->decrementJailCards();
                        p->setJail(false);
                        cout << "\033[2J\033[H"; // clears and resets the terminal 
                        board.displayOverview();
                        cout << "Get out of Jail Card used. Enter a character to roll the die: ";
                        cin >> response;
                    }
                }

                if (p->isJailed() > 0) {
                    char responseChar;
                    do {
                        cout << "Would you like to pay $50 to get out of jail? (y/n): ";
                        cin >> response;
                        responseChar = tolower(response.at(0));
                    } while (responseChar != 'y' && responseChar != 'n'); 

                    if (responseChar == 'y') {
                        p->removeBalance(50);
                        p->setJail(false);
                        cout << "\033[2J\033[H"; // clears and resets the terminal 
                        board.displayOverview();
                        cout << "Paid. Enter a character to roll the die: ";
                        cin >> response;
                    }
                }
                
                if (p->isJailed()) {
                    cout << "Enter a character to roll the die: ";
                    cin >> response;
                    int rollOne = D1.roll();
                    int rollTwo = D2.roll();
                    cout << "You rolled " << rollOne << " and " << rollTwo;
                    

                    if (rollOne == rollTwo) {
                        p->setJail(false);
                        fromJail = true;
                        spaces = rollOne + rollTwo;
                        cout << ". Getting out of jail...\n";
                        prevMessage = "Rolled doubles to get out of jail";
                    }
                    else {
                        cout << ". You stay in jail\n"; 
                        p->incrementTurnsInJail();
                    }

                    if (p->getTurnsInJail() >= 3) {
                        cout << "You must pay $50 to leave jail. Enter a character to acknowledge: ";
                        cin >> response;
                        spaces = rollOne + rollTwo;
                        p->removeBalance(50);
                        p->setJail(false);
                    }
                    this_thread::sleep_for(chrono::milliseconds(1500));
                }
            }

            cout << "\033[2J\033[H"; // clears and resets the terminal 


            if (!p->isJailed()) {
                if (!fromJail) {
                    spaces = roll(D1, D2);
                }

                /// Print board for each piece move
                for (int i = 0; i < spaces; i++) {
                    cout << "\033[38A"; // number before A indicates how many lines cursor moves up
                    p->move(1);
                    cout << "Moving (" << spaces << ")" << "..." << setw(100) << '\n';
                    board.displayOverview();
                    this_thread::sleep_for(chrono::milliseconds(250));
                }

                Property* newProp = findById(&properties, p->getPosition());
                if (newProp->isBuyable() && newProp->getOwnerId() != p->getId() && newProp->getOwnerId() != -1) {
                    cout << "You owe " << newProp->getRent() << ". Pay by entering a character: ";
                    cin >> prevMessage;
                    pay(*p, players.at(findById(players, newProp->getOwnerId())), newProp->getRent());
                }

                if (!fromJail) {
                    prevMessage = p->getName() + " rolled and moved " + to_string(spaces) + " spaces";
                }
                else {
                    prevMessage = p->getName() + " rolled doubles and moved " + to_string(spaces) + " spaces to get out of jail";
                }
                doOption = true;
            }

            if (p->getPosition() == 30) {
                cout << "You landed on \"Go To Jail \". Enter a character to acknowledge: ";
                cin >> prevMessage;
                p->setJail(true);
                prevMessage = p->getName() + " went to jail";
                doOption = false;
            }
            
            if (!doOption) {
                cyclePlayers(players);
            }
        }
        else if (action == 'h') {
            prevMessage = showActions();
            this_thread::sleep_for(chrono::seconds(5));
        }
        else if (action == 'u') {
            Player *currentPlayer = &players.at(0);
            cout << "\033[2J\033[H"; // clears and resets the terminal 
            board.displayPlayerProperties(*currentPlayer, "upgrade");
            string input;
            cout << "Input the property ID to upgrade (enter a character to exit without upgrading): ";
            cin >> input;
            if (isdigit(input.at(0))) {
                for (size_t i = 0; i < currentPlayer->getPropertiesOwned().size(); i++) {
                    Property *p = currentPlayer->getPropertiesOwned().at(i);
                    if (stoi(input) == p->getId()) {
                        // prevMessage = upgradeProperty(currentPlayer, stoi(input));
                        if (p->getOwnerId() != currentPlayer->getId()) {
                            prevMessage = "Can not upgrade a property you do not own";
                        }
                        else {
                            int status = isUpgradable(*p, currentPlayer->getPropertiesOwned());
                            // cout << status << endl;
                            if (status == 0) {
                                p->upgrade();
                                currentPlayer->removeBalance(50);
                                prevMessage = "Upgraded " + p->getName() + ". Rent is now " + to_string(p->getRent());
                            }
                            else if (status == 1) {
                                prevMessage = "You must upgrade your other " + p->getType() + " properties to level " + to_string(p->getUpgradeCount());
                            }
                            else if (status == 2) {
                                prevMessage = "You must own all " + p->getType() + " property types";
                            }
                            else if (status == 3) {
                                prevMessage = "You have already upgraded this property all the way";
                            }
                        }

                        break;
                    }
                    else {
                        prevMessage = input + " is not owned by you";
                    }
                }
            }
            else {
                prevMessage = "Exited without upgrading any properties";
            }


            
            // Property *currrentlyOn = findById(&properties, currentPlayer->getPosition());
        }
        else if (action == 's') {
            cout << "\033[2J\033[H";
            board.displayProperties();
            cout << "Enter a character to exit: ";
            cin >> prevMessage;
            prevMessage = "Exited property display menu";
        }

        cout << "\033[2J\033[H"; // clears and resets the terminal 


        if (!prevMessage.empty()) {
            cout << prevMessage << '\n';
        }

        while (doOption) {
            board.displayOverview();
            char option = getOption();

            if (option == 'o') {
                prevMessage = players.at(0).getName() + " played through";
                cyclePlayers(players);
                doOption = false;
            }
            else if (option == 'b') { // could add a verification here...
                Player *currentPlayer = &players.at(0);
                Property *currrentlyOn = findById(&properties, currentPlayer->getPosition());
                if (currrentlyOn->isBuyable() && currrentlyOn->getOwnerId() == -1) {
                    currentPlayer->addProperty(currrentlyOn);
                    currrentlyOn->setOwnerId(currentPlayer->getId());
                    currentPlayer->removeBalance(currrentlyOn->getPrice());
                    prevMessage = currentPlayer->getName() + " bought " + currrentlyOn->getName() + " for " + to_string(currrentlyOn->getPrice());
                }
                else {
                    prevMessage = currrentlyOn->getName() + " is not buyable or is already owned";
                }
            }
            else if (option == 's') {
                string input;
                Player *currentPlayer = &players.at(0);
                // Property *currrentlyOn = findById(&properties, currentPlayer->getPosition());
                cout << "\033[2J\033[H"; // clears and resets the terminal 
                board.displayPlayerProperties(*currentPlayer, "sell");
                cout << "Input the property ID to sell (enter a character to exit without selling): ";
                cin >> input;
                if (isdigit(input.at(0))) {
                    for (size_t i = 0; i < currentPlayer->getPropertiesOwned().size(); i++) {
                        Property *p = currentPlayer->getPropertiesOwned().at(i);
                        if (stoi(input) == p->getId()) {
                            p->setOwnerId(-1);
                            int amount = p->getPrice() / 2; // this is incorrect, there are set mortgage values -- this will do for now
                            if (p->getUpgradeCount() > 0) {
                                for (size_t j = 0; j < currentPlayer->getPropertiesOwned().size(); j++) {
                                    if (p->getType() == currentPlayer->getPropertiesOwned().at(j)->getType()) {
                                        amount = amount + (currentPlayer->getPropertiesOwned().at(j)->getUpgradeCount() * 50) / 2;
                                        currentPlayer->getPropertiesOwned().at(j)->setUpgradeCount(0);
                                    }
                                }
                            }

                            currentPlayer->addBalance(amount);
                            currentPlayer->removeProperty(i);
                            
                            prevMessage = "Sold " + p->getName() + " for " + to_string(amount);
                            break;
                        }
                        else {
                            prevMessage = input + " is not owned by you";
                        }
                    }
                }
                else {
                    prevMessage = "Exited without selling any properties";
                }
            }
            else if (option == 'h') {
                prevMessage = showOptions();
                this_thread::sleep_for(chrono::seconds(5));
            }
            else if (option == 'u') {
                Player *currentPlayer = &players.at(0);
                cout << "\033[2J\033[H"; // clears and resets the terminal 
                board.displayPlayerProperties(*currentPlayer, "upgrade");
                string input;
                cout << "Input the property ID to upgrade (enter a character to exit without upgrading): ";
                cin >> input;
                if (isdigit(input.at(0))) {
                    for (size_t i = 0; i < currentPlayer->getPropertiesOwned().size(); i++) {
                        Property *p = currentPlayer->getPropertiesOwned().at(i);
                        if (stoi(input) == p->getId()) {
                            // prevMessage = upgradeProperty(currentPlayer, stoi(input));
                            if (p->getOwnerId() != currentPlayer->getId()) {
                                prevMessage = "Can not upgrade a property you do not own";
                            }
                            else {
                                int status = isUpgradable(*p, currentPlayer->getPropertiesOwned());
                                // cout << status << endl;
                                if (status == 0) {
                                    p->upgrade();
                                    currentPlayer->removeBalance(50);
                                    prevMessage = "Upgraded " + p->getName() + ". Rent is now " + to_string(p->getRent());
                                }
                                else if (status == 1) {
                                    prevMessage = "You must upgrade your other " + p->getType() + " properties to level " + to_string(p->getUpgradeCount());
                                }
                                else if (status == 2) {
                                    prevMessage = "You must own all " + p->getType() + " property types";
                                }
                                else if (status == 3) {
                                    prevMessage = "You have already upgraded this property all the way";
                                }
                            }

                            break;
                        }
                        else {
                            prevMessage = input + " is not owned by you";
                        }
                    }
                }
                else {
                    prevMessage = "Exited without upgrading any properties";
                }
            }

            cout << "\033[2J\033[H"; // clears and resets the terminal 

            if (!prevMessage.empty()) {
                cout << prevMessage << '\n';
            }
        } 

    } while(play);


    



    // cout << "\033[2J\033[H"; // clears and resets the terminal (use once program ends)
    return 0;
}/// main

bool duplicateId(const int &newId, const vector<Property> &properties) {
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

bool verifyQuit() {
    string response;
    do {
        cout << "All progress will be lost. Confirm you wish to quit the game. (y/n): ";
        cin >> response;

        if (tolower(response.at(0)) == 'y') {
            cout << "Quitting the game" << endl;
            return true;
        }
        else if (tolower(response.at(0)) == 'n') {
            cout << "The game will continue" << endl;
            return false;
        }
    } while(response.at(0) != 'y' || response.at(0) != 'n');

    return false;
}

string showActions() {
    cout << "\033[30A"; // number before A indicates how many lines cursor moves up
    cout << "\033[8CACTIONS:" << "\r\n";
    cout << "\033[8Cr - roll the dice" << "\r\n";
    cout << "\033[8Cu - upgrade current property" << "\r\n";
    cout << "\033[8Ch - show actions" << "\r\n";
    cout << "\033[8Cs - show properties" << "\r\n";
    cout << "\033[8Cq - quit the game" << "\r\n";
    // add change identifier and save game once we get there
    return "ACTIONS: r - roll the dice, u - upgrade current property, h - show actions, s - show properties, q - quit the game";
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

char getAction() {
    string action;
    bool validChoice = false;
    do {
        cout << "Action: ";
        cin >> action;
        char c = tolower(action.at(0));
        if (c == 'q' || c == 'r' || c == 'u' || c == 'p' || c == 'h' || c == 's') {
            return c;
        }
        else {
            cout << "Invalid action. Input 'h' for help" << endl;
        }
    } while (!validChoice);

    return 'q';
}

void pay(Player &p1, Player &p2, const int &amount) {
    if (p1.getBalance() < amount) {
        cout << "Insufficient funds" << endl;
    }
    else {
        p1.setBalance(p1.getBalance() - amount);
        p2.setBalance(p2.getBalance() + amount);
    }
}

string showOptions() {
    cout << "\033[30A"; // number before A indicates how many lines cursor moves up
    cout << "\033[8COPTIONS:" << "\r\n";
    cout << "\033[8Co/r - onward" << "\r\n";
    cout << "\033[8Cb - buy property" << "\r\n";
    cout << "\033[8Cs - sell property" << "\r\n";
    cout << "\033[8Cu - upgrade property" << "\r\n";
    cout << "\033[8Ch - show options" << "\r\n";
    // add change identifier and save game once we get there
    return "OPTIONS: o - onward, b - buy property, s - sell property, u - upgrade property, h - show options";
}

char getOption() {
    string action;
    bool validChoice = false;
    do {
        cout << "Option: ";
        cin >> action;
        char c = tolower(action.at(0));
        if (c == 'o' || c == 'b' || c == 's' || c == 'u' || c == 'h') {
            return c;
        }
        else if (c == 'r') {
            return 'o';
        }
        else {
            cout << "Invalid action. Input 'h' for help" << endl;
        }
    } while (!validChoice);

    return 'o';
}

