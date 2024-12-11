#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "board.h"
#include <vector>
#include <cctype>
using namespace std;

Board::Board(vector<Property> *pps, vector<Player> *pls) {
    properties = pps;
    players = pls;
    updatePositions();
    setPropSubNames();

}

void Board::outputTest() {
    updatePositions();
    cout << "Properties:" << endl;
    for (size_t i = 0; i < properties->size(); i++) {
        cout << properties->at(i).getName() << endl;
    }

    cout << "Players" << endl;
    for (size_t i = 0; i < players->size(); i++) {
        cout << players->at(i).getName() << endl;
    }

    cout << "Map" << endl;
    for (auto itr = ppos.begin(); itr != ppos.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second
             << '\n';
    }

    cout << "Subnames" << endl;
    for (size_t i = 0; i < propSubNames.size(); i++) {
        cout << propSubNames.at(i) << endl;
    }
    cout << endl;
}

void Board::updatePositions() {
    for (size_t i = 0; i < players->size(); i++) {
        ppos[players->at(i).getId()] = convertToBoardPos(players->at(i).getPosition());
    }
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


void Board::outputBoard() {
    int propNum = 0;
    for (int i = 0; i < 34; i++) {
        // if (propNum > 10) { propNum = 10; }
        for (int j = 0; j < 56; j++) {
            /// Top and bottom property names
            if ((i == 1 || i == 31) && j % 5 == 1) {
                cout << propSubNames.at(propNum);
                propNum++;
            }
            /// Horizontal lines for top and bottom 
            else if (i == 0 || i == 3 || i == 30 || i == 33) {
                if (j % 5 == 0) {
                    cout << "+";
                }
                else {
                    cout << "-";
                }
            }
            /// Horizontal lines for down the sides
            else if (i % 3 == 0) {
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
            else if ((i > 0 && i < 3) || (i > 30 && i < 34)) {
                if (j % 5 == 0) {
                    cout << "|";
                }
                else if (i != 1 && i != 31) {
                    cout << " ";
                }
            }
            /// Down the sides
            else {
                if (j == 0 || j == 5 || j == 50 || j == 55) {
                    cout << "|";
                }
                else if (i % 3 == 1 && (j == 1 || j == 51)) {
                    cout << propSubNames.at(propNum);
                    propNum++;
                }
                else if (i % 3 == 2 || (j > 5 && j < 51)) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    cout << "\033[34A"; // number before A indicates how many lines
}