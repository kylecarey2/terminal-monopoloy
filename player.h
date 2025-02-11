#ifndef PLAYER_H
#define PLAYER_H
#include <iomanip>
#include <vector>
#include "property.h"

class Player{
public:
    Player();
    Player(int newId);
    Player(int newId, string newName);

    int getId() const;
    int getBalance() const;
    int getPosition() const;
    string getName() const;
    vector<Property*> getPropertiesOwned() const;
    int getJailCards() const;
    bool isJailed() const;

    void setId(int newId);
    void setBalance(int newBalance);
    void setPosition(int newPos);
    void setName(string newName);
    void setJail(bool j);
    int getTurnsInJail();
    void incrementTurnsInJail();
    
    
    void addBalance(int amount);
    void removeBalance(int amount);
    void incrementJailCards();
    void decrementJailCards();
    void addProperty(Property *p);
    void removeProperty(size_t index);
    void move(int num);
    friend Player* findById(vector<Player> *players, int id);
    friend int findById(const vector<Player> &players, int id);



private:
    int id;         /// number 0-whatever representing the player
    int balance;    /// player's balance
    int pos;   /// player's position on the board
    string name;
    vector<Property*> propertiesOwned;

    int jailCards;  /// number of get out of jail cards
    bool inJail;
    int turnsInJail;
};
#endif