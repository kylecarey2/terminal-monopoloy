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
}

Player::Player(int newId) {
    id = newId > -1 ? newId : -1;

    balance = 1500;
    pos = 0;
    name = "-";
    jailCards = 0;
    inJail = false;
}

Player::Player(int newId, string newName) {
    id = newId > -1 ? newId : -1;
    name = !newName.empty() ? newName : "-";

    pos = 0;
    balance = 1500;
    jailCards = 0;
    inJail = false;
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

vector<Property> Player::getPropertiesOwned() const {
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

void Player::addProperty(Property p) {
    propertiesOwned.push_back(p);
}

void Player::move(int num) {
    if (pos + num > 39) {
        pos = (pos + num) % 39;
    }
    else {
        pos = pos + num;
    }
}