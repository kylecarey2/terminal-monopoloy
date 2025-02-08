#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "board.h"
#include "property.h"
#include <vector>
#include <cctype>
// #include <string>
using namespace std;

Board::Board(vector<Property> *pps, vector<Player> *pls) {
    properties = pps;
    players = pls;
    setPropSubNames();

}

void Board::outputTest() {
    cout << "Properties:" << endl;
    for (size_t i = 0; i < properties->size(); i++) {
        cout << properties->at(i).getName() << endl;
    }

    cout << "Players" << endl;
    for (size_t i = 0; i < players->size(); i++) {
        cout << players->at(i).getName() << endl;
    }

    cout << "Subnames" << endl;
    for (size_t i = 0; i < propSubNames.size(); i++) {
        cout << propSubNames.at(i) << endl;
    }
    cout << endl;
}

void Board::setPropSubNames() {
    for (size_t i = 0; i < properties->size(); i++) {
        string sub = properties->at(i).getName().substr(0, 4);
        for (size_t i = 0; i < sub.length(); i++) {
            sub.at(i) = toupper(sub.at(i));
        }

        if(sub.length() == 1) {
            sub.insert(sub.begin(), ' ');
            sub.insert(sub.end(), ' ');
            sub.insert(sub.end(), ' ');
        }
        else if (sub.length() == 2) {
            sub.insert(sub.begin(), ' ');
            sub.insert(sub.end(), ' ');
        }
        else if (sub.length() == 3) {
            sub.insert(sub.end(), ' ');
        }

        propSubNames.push_back(sub);
    }
}

int Board::convertToBoardPos(int playerPos) {
    switch (playerPos) {
        case 20:
            return 0;
        case 21:
            return 1;
        case 22:
            return 2;
        case 23:
            return 3;
        case 24:
            return 4;
        case 25:
            return 5;
        case 26:
            return 6;
        case 27:
            return 7;
        case 28:
            return 8;
        case 29:
            return 9;
        case 30:
            return 10;
        case 19:
            return 11;
        case 31:
            return 12;
        case 18:
            return 13;
        case 32:
            return 14;
        case 17:
            return 15;
        case 33:
            return 16;
        case 16:
            return 17;
        case 34:
            return 18;
        case 15:
            return 19;
        case 35:
            return 20;
        case 14:
            return 21;
        case 36:
            return 22;
        case 13:
            return 23;
        case 37:
            return 24;
        case 12:
            return 25;
        case 38:
            return 26;
        case 11:
            return 27;
        case 39:
            return 28;
        case 10:
            return 29;
        case 9:
            return 30;
        case 8:
            return 31;
        case 7:
            return 32;
        case 6:
            return 33;
        case 5:
            return 34;
        case 4:
            return 35;
        case 3:
            return 36;
        case 2:
            return 37;
        case 1:
            return 38;
        case 0:
            return 39;
        default:
            cout << "Error: could not translate player position to board position" << endl;
            exit(0);
    };
}


void Board::displayOverview() {
    /// Current Player
    Player currentPlayer = players->at(0);
    int currentPropOwned = currentPlayer.getPropertiesOwned().size() < 16 ? currentPlayer.getPropertiesOwned().size() : 15;
    int currentPropOwnedIter = 0;
    Property *currentPropOn = findById(properties, currentPlayer.getPosition());

    /// Next Player
    Player nextPlayer = players->at(1);
    int nextPropOwned = nextPlayer.getPropertiesOwned().size() < 16 ? nextPlayer.getPropertiesOwned().size() : 15;
    int nextPropOwnedIter = 0;
    Property *nextPropOn = findById(properties, nextPlayer.getPosition());

    /// Due up players
    size_t playerNum = players->size() > 2 ? players->size() : 1;
    size_t playerNumIter = playerNum == 1 ? 0 : 2;

    /// PROPERTY AND PLAYER ITERATORS
    int propNumIter = 0;
    int spotsCountIter = 0;

    cout << "\033[?25l"; // removes cursor so output does not "glitch"
    for (int i = 0; i < 35; i++) {
        /// Board horizontal lines
        for (int j = 0; j < 56; j++) {
            /// Top and bottom property names
            if (i == 0) {
                if (j == 0) {
                    cout << "Board:" << setw(50); 
                    cout << "";
                }
            }
            else if ((i == 2 || i == 32) && j % 5 == 1) {
                cout << propSubNames.at(propNumIter);
                propNumIter++;
            }
            /// Horizontal lines for top and bottom 
            else if (i == 1 || i == 4 || i == 31 || i == 34) {
                if (j % 5 == 0) {
                    cout << "+";
                }
                else {
                    cout << "-";
                }
            }
            /// Horizontal lines for down the sides
            else if (i % 3 == 1) {
                if (j > 5 && j < 50) {
                    cout << " ";
                }
                else if (j % 5 == 0) {
                    cout << "+";
                }
                else {
                    cout << "-";
                }
            }
            /// Vertical lines for top and bottom rows
            else if ((i > 1 && i < 4) || (i > 31 && i < 35)) {
                if (j % 5 == 0) {
                    cout << "|";
                }
                else if ((i != 2 && i != 32) && j % 5 == 1) {
                    outputPPos(spotsCountIter);
                    spotsCountIter++;
                }
            }
            /// Down the sides
            else {
                if (j == 0 || j == 5 || j == 50 || j == 55) {
                    cout << "|";
                }
                else if (i % 3 == 2 && (j == 1 || j == 51)) {
                    cout << propSubNames.at(propNumIter);
                    propNumIter++;
                }
                else if (j > 5 && j < 51) {
                    cout << " ";
                }
                else if (j % 5 == 1) {
                    outputPPos(spotsCountIter);
                    spotsCountIter++;
                }
            }
        }
        
        /// Player dashboard horizontal lines
        cout << right;
        cout << setw(7);
        cout << " ";
        for (int j = 0; j < 76; j++) {
            /// Table Headers
            if (i == 0) {
                if (j == 0) {
                    cout << setw(30);
                    cout << left << "Current Player:";
                }
                else if (j == 25) {
                    cout << setw(30);
                    cout << left << "Next Player:";
                }
                else if (j == 50) {
                    cout << left << "Due Up:";
                }
            }
            /// Table horizontal top line
            else if (i == 1) {
                if (j == 29 || j == 59) {
                    cout << "+";
                }
                else {
                    cout << "-";
                }
            }

            /// First column data
            else if (j == 0) {
                if (i == 2) {
                    cout << "Name: " << currentPlayer.getName() << setw(30 - (6 + currentPlayer.getName().length()));
                }
                else if (i == 3) {
                    cout << "Balance: " << currentPlayer.getBalance() << setw(30 - (9 + to_string(currentPlayer.getBalance()).length()));
                }
                else if (i == 4) {
                    cout << "In Jail: "; 
                    if (currentPlayer.isJailed()) {
                        cout << "Yes" << setw(18);
                    }
                    else {
                        cout << "No" << setw(19);
                    }
                }
                else if (i == 5) {
                    cout << "Get out of Jail Cards: " << currentPlayer.getJailCards() << setw(30 - (23 + to_string(currentPlayer.getJailCards()).length()));
                }
                else if (i == 6) {
                    cout << "Properties Owned: " << currentPlayer.getPropertiesOwned().size() << setw(30 - (18 + to_string(currentPlayer.getPropertiesOwned().size()).length()));
                }
                else if (currentPropOwnedIter < currentPropOwned) {
                    cout << " -" << currentPlayer.getPropertiesOwned().at(currentPropOwnedIter)->getName() << setw(30 - (2 + currentPlayer.getPropertiesOwned().at(currentPropOwnedIter)->getName().length()));
                    currentPropOwnedIter++;
                }
                else if (i == 8 + currentPropOwned) {
                    cout << "Currently On: " << currentPropOn->getName() << setw(30 - (14 + currentPropOn->getName().length()));
                }
                else if (i == 9 + currentPropOwned) {
                    cout << "Owned By: "; 
                    if (!currentPropOn->isBuyable()) {
                        cout << "Not Ownable" << setw(9);
                    }
                    else if (currentPropOn->getOwnerId() == -1) {
                        cout << "Nobody" << setw(14);
                    }
                    else {
                        cout << findById(players, currentPropOn->getOwnerId())->getName() << setw(30 - (10 + findById(players, currentPropOn->getOwnerId())->getName().length()));
                    }
                }
                else if (i == 10 + currentPropOwned) {
                    if (currentPropOn->getOwnerId() == -1) {
                        cout << "Cost: " << currentPropOn->getPrice() << setw(30 - (6 + to_string(currentPropOn->getPrice()).length()));
                    }
                    else if (currentPropOn->getOwnerId() == currentPlayer.getId()) {
                        cout << "Pays: " << currentPropOn->getRent() << setw(30 - (6 + to_string(currentPropOn->getRent()).length())); // change getPrice to the member data that shows how much a player pays if landed on
                    }
                    else if (currentPropOn->getOwnerId() > -1) {
                        cout << "You Owe(d): " << currentPropOn->getRent() << setw(30 - (12 + to_string(currentPropOn->getRent()).length())); // change getPrice to the member data that shows how much a player pays if landed on
                    }
                    // also add another else if seeing if it is not ownable and then just setw(30);
                }
                else {
                    cout << setw(30);
                }
                cout << "|";
            }
            /// Second Column data
            else if (j == 26) {
                if (i == 2) {
                    cout << "Name: " << nextPlayer.getName() << setw(30 - (6 + nextPlayer.getName().length()));
                }
                else if (i == 3) {
                    cout << "Balance: " << nextPlayer.getBalance() << setw(30 - (9 + to_string(nextPlayer.getBalance()).length()));
                }
                else if (i == 4) {
                    cout << "In Jail: "; 
                    if (nextPlayer.isJailed()) {
                        cout << "Yes" << setw(18);
                    }
                    else {
                        cout << "No" << setw(19);
                    }
                }
                else if (i == 5) {
                    cout << "Get out of Jail Cards: " << nextPlayer.getJailCards() << setw(30 - (23 + to_string(nextPlayer.getJailCards()).length()));
                }
                else if (i == 6) {
                    cout << "Properties Owned: " << nextPlayer.getPropertiesOwned().size() << setw(30 - (18 + to_string(nextPlayer.getPropertiesOwned().size()).length()));
                }
                else if (nextPropOwnedIter < nextPropOwned) {
                    cout << " -" << nextPlayer.getPropertiesOwned().at(nextPropOwnedIter)->getName() << setw(30 - (2 + nextPlayer.getPropertiesOwned().at(nextPropOwnedIter)->getName().length()));
                    nextPropOwnedIter++;
                }
                else if (i == 8 + nextPropOwned) {
                    cout << "Currently On: " << nextPropOn->getName() << setw(30 - (14 + nextPropOn->getName().length()));
                }
                else if (i == 9 + nextPropOwned) {
                    cout << "Owned By: "; 
                    if (!nextPropOn->isBuyable()) {
                        cout << "Not Ownable" << setw(9);
                    }
                    else if (nextPropOn->getOwnerId() == -1) {
                        cout << "Nobody" << setw(14);
                    }
                    else {
                        cout << findById(players, nextPropOn->getOwnerId())->getName() << setw(30 - (10 + findById(players, nextPropOn->getOwnerId())->getName().length()));
                    }
                }
                else if (i == 10 + nextPropOwned) {
                    if (nextPropOn->getOwnerId() == -1) {
                        cout << "Cost: " << nextPropOn->getPrice() << setw(30 - (6 + to_string(nextPropOn->getPrice()).length()));
                    }
                    else if (nextPropOn->getOwnerId() == nextPlayer.getId()) {
                        cout << "Pays: " << nextPropOn->getRent() << setw(30 - (6 + to_string(nextPropOn->getRent()).length())); // change getPrice to the member data that shows how much a player pays if landed on
                    }
                    else if (nextPropOn->getOwnerId() > -1) {
                        cout << "You Owe(d): " << nextPropOn->getRent() << setw(30 - (12 + to_string(nextPropOn->getRent()).length())); // change getPrice to the member data that shows how much a player pays if landed on
                    }
                    // also add another else if seeing if it is not ownable and then just setw(30);
                }
                else {
                    cout << setw(30);
                }
                cout << "|";
            }
            /// Third column data "stack" of upcoming players
            else if (j == 51) {
                if (playerNumIter < playerNum) {
                    cout << players->at(playerNumIter).getName();
                    playerNumIter++;
                }
            }
        }      
        cout << "\r\n";
    }
    
    cout << "\033[?25h"; // puts cursor back
}

void Board::outputPPos(int boardPos) {
    int spotsTaken = 0;
    string output = "";
    for (size_t i = 0; i < players->size(); i++) {
        if (spotsTaken == 4) {
            break;
        }

        int ppos = convertToBoardPos(players->at(i).getPosition());
        if (ppos == boardPos) {
            if (i == 0) {
                output = output + "\e[32m" + static_cast<char>(toupper(players->at(i).getName().at(0))) + "\e[0m";
            }
            else {
                output += toupper(players->at(i).getName().at(0));
            }

            spotsTaken++;
        }
    }

    for (int i = 4; i > spotsTaken; i--) {
        output.insert(output.end(), ' ');
    }

    cout << output;
}

void Board::displayProperties() {
    /// variables
    size_t playerCount = players->size(); 
    int SPACE = 140 / playerCount;
    size_t propCount = 0;

    /// how to read
    cout << "Property names are listed next to '-' with the property ID in () to the right of the name" << '\n';
    cout << "Property types are listed next to '^' with the property upgrade count in () to the right of the type" << "\n\n";

    for (int i = 0; i < 33; i++) {
        size_t playerItr = 0; // reset every row
        if (i == 0) {
            cout << "Player Properties Owned:";
        }
        else if (i > 5 && i % 2 == 0) { // only increment on evens to keep same data for ^ section
            propCount++;
        }

        cout << right;
        for (int j = 0; j < 136; j++) {
            if (i == 1) {
                if (playerItr < playerCount) {
                    cout << left << setw(SPACE) << players->at(playerItr).getName();
                    playerItr++;
                }
            }
            else if (i == 2) {
                if (j % SPACE == SPACE - 1 && j != 135) {
                    cout << "+";
                } 
                else {
                    cout << "-";
                }
            }
            else if (j % SPACE == 0) {
                if (i == 3) {
                    if (playerItr < playerCount) {
                        cout << "Owned: " << players->at(playerItr).getPropertiesOwned().size() << setw(SPACE - (7 + (to_string(players->at(playerItr).getPropertiesOwned().size()).length())));
                        playerItr++;
                    }
                }
                else if (i == 4) {
                    cout << setw(SPACE);
                    playerItr++;
                }
                else if (i == 5) {
                    cout << "Properties:" << setw(SPACE - 11);
                    playerItr++;
                }
                else if (i > 5) {
                    if (propCount - 1 < players->at(playerItr).getPropertiesOwned().size()) {
                        string prop;
                        if (i % 2 == 0) {
                            prop = "-" + players->at(playerItr).getPropertiesOwned().at(propCount - 1)->getName() + " (" + to_string(players->at(playerItr).getPropertiesOwned().at(propCount - 1)->getId()) + ")";
                        }
                        else {
                            prop = " ^" + players->at(playerItr).getPropertiesOwned().at(propCount - 1)->getType() + " (" + to_string(players->at(playerItr).getPropertiesOwned().at(propCount - 1)->getUpgradeCount()) + ")";
                        }
                        if (prop.length() > SPACE) {
                            prop = prop.substr(0, SPACE - 1);
                        }

                        cout << prop << setw(SPACE - prop.length());
                    }
                    else {
                        cout << setw(SPACE);
                    }
                    
                    playerItr++;  
                }

                if (i > 1 && playerItr < playerCount) {
                    cout << "|";
                }
            }
        }
        cout << "\r\n";
    }
}

void Board::displayPlayerProperties(Player &p, const string &msg) {
    // Player p = players->at(0);
    size_t propItr = 0;
    size_t propSize = p.getPropertiesOwned().size();
    int longestPropName = 0;
    int longestTypeName = 0;
    for (size_t i = 0; i < p.getPropertiesOwned().size(); i++) {
        if (p.getPropertiesOwned().at(i)->getName().length() > longestPropName) { longestPropName = p.getPropertiesOwned().at(i)->getName().length(); }
        if (p.getPropertiesOwned().at(i)->getType().length() > longestTypeName) { longestTypeName = p.getPropertiesOwned().at(i)->getType().length(); }
    }


    cout << "Reference the ID to " << msg << " a certain property" << "\n\n";
    cout << left;
    for (size_t i = 0; i < 33; i++) {
        if (i == 0) {
            cout << p.getName() << " properties owned:";
        }
        else if (i == 2) {
            for (int j = 0; j < 13 + longestPropName + longestTypeName; j++) { cout << "-"; }
        }
        else if (i == 1) {
            cout << setw(4) << "ID" << setw(2 + longestPropName) << "Name" << setw(2 + longestTypeName) << "Type" << "Level";
        }
        else if (propItr < propSize) {
            cout << setw(2) << p.getPropertiesOwned().at(propItr)->getId() << "  "
                << setw(longestPropName) << p.getPropertiesOwned().at(propItr)->getName() << "  "
                << setw(longestTypeName) << p.getPropertiesOwned().at(propItr)->getType() << "  "
                << p.getPropertiesOwned().at(propItr)->getUpgradeCount();

            propItr++;
        }

        cout << "\n";
    }
    cout << right;
}