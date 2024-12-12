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
    void outputBoard();
private:
    void outputPPos(int boardPos);
    void setPropSubNames();
    int convertToBoardPos(int playerPos);
    const vector<Property> *properties;
    const vector<Player> *players;
    vector<string> propSubNames;
};