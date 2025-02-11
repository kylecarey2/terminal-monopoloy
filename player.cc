#include "property.h"
#include "player.h"
#include <cstdlib>
using namespace std;

/// Constructors
Player::Player() {
    id = -1;
    balance = 1500;
    pos = 0;
    name = "-";
    jailCards = 0;
    inJail = false;
    turnsInJail = 0;
}

Player::Player(int newId) {
    id = newId > -1 ? newId : -1;

    balance = 1500;
    pos = 0;
    name = "-";
    jailCards = 0;
    inJail = false;
    turnsInJail = 0;

}

Player::Player(int newId, string newName) {
    id = newId > -1 ? newId : -1;
    name = !newName.empty() ? newName : "-";

    pos = 0;
    balance = 1500;
    jailCards = 0;
    inJail = false;
    turnsInJail = 0;

}


/// Getters
int Player::getId() const {
    return id;
}

int Player::getBalance() const {
    return balance;
}

int Player::getPosition() const {
    return pos;
}

string Player::getName() const {
    return name;
}

vector<Property*> Player::getPropertiesOwned() const {
    return propertiesOwned;
}

int Player::getJailCards() const {
    return jailCards;
}

bool Player::isJailed() const {
    return inJail;
}

/// Setters
void Player::setId(int newId) {
    if (newId > -1) {
        id = newId;
    }
}

void Player::setBalance(int newBalance) {
    balance = newBalance;
}

void Player::setPosition(int newPos) {
    if (newPos > 0 && newPos < 40) {
        pos = newPos;
    }
}

void Player::setName(string newName) {
    if (!newName.empty()) {
        name = newName;
    }
}

void Player::setJail(bool j) {
    if (j) {
        setPosition(10);
    }
    inJail = j;
}

void Player::addBalance(int amount) {
    if (amount >= 0) {
        balance += amount;
    }
}

void Player::removeBalance(int amount) {
    if (amount >= 0) {
        balance -= amount;
    }
}

void Player::incrementJailCards() {
    jailCards++;
}

void Player::decrementJailCards() {
    if (jailCards > 0) {
        jailCards--;
    }
}

int Player::getTurnsInJail() {
    return turnsInJail;
}

void Player::incrementTurnsInJail() {
    if (turnsInJail < 3) {
        turnsInJail++;
    }
    else {
        turnsInJail = 0;
    }
}

void Player::addProperty(Property *p) {
    propertiesOwned.push_back(p);
}

void Player::removeProperty(size_t index) {
    propertiesOwned.erase(propertiesOwned.begin() + index);
}


void Player::move(int num) {
    if (pos + num > 39) {
        pos = (pos + num) % 39 - 1;
    }
    else {
        pos = pos + num;
    }
}

Player* findById(vector<Player> *players, int id) {
    for (size_t i = 0; i < players->size(); i++) {
        if (players->at(i).id == id) {
            return &players->at(i);
        }
    }

    return nullptr;
}

int findById(const vector<Player> &players, int id) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players.at(i).id == id) {
            return i;
        }
    }

    return -1;
}