#include <cstdlib>
#include "property.h"
#include "player.h"
#include <vector>
#include <map>
using namespace std;

class Board {
public:
    Board(vector<Property> *pps, vector<Player> *pls);
    void outputTest();
    void displayOverview();
    void displayProperties();
private:
    // void displayBoard(const int &i);
    // void displayDashboard(const int &i);
    void outputPPos(int boardPos);
    void setPropSubNames();
    int convertToBoardPos(int playerPos);
    vector<Property> *properties;
    vector<Player> *players;
    vector<string> propSubNames;
};