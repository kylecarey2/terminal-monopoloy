#include "property.h"
#include "player.h"
#include <cstdlib>
using namespace std;

/// Constructors
Player::Player() {
    id = -1;
    balance = 1500;
    name = "-";
    jailCards = 0;
    inJail = false;
}

Player::Player(int newId) {
    id = newId > -1 ? newId : -1;

    balance = 1500;
    name = "-";
    jailCards = 0;
    inJail = false;
}

Player::Player(int newId, string newName) {
    id = newId > -1 ? newId : -1;
    name = !newName.empty() ? newName : "-";

    balance = 1500;
    jailCards = 0;
    inJail = false;
}


/// Getters
int Player::getId() {
    return id;
}

int Player::getBalance() {
    return balance;
}

string Player::getName() {
    return name;
}

vector<Property> Player::getPropertiesOwned() {
    return propertiesOwned;
}

int Player::getJailCards() {
    return jailCards;
}

bool Player::isJailed() {
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