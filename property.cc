#include "property.h"

#include <cstdlib>

Property::Property() {
    id = -1;
    price = -1;
    name = "-";
    type = "-";
    ownerId = -1;
    buyable = false;
    // rent = -1;
    upgradeCount = 0;
}  /// Property

Property::Property(int newId) {
    if (newId > -1) {
        id = newId;
    }
    else {
        id = -1;
    }

    price = -1;
    name = "-";
    type = "-";
    ownerId = -1;
    buyable = false;
    // rent = -1;
    upgradeCount = 0;
}  /// Property

Property::Property(string propertyData) {
    // id|name|price|rent|type
    /// DOES NOT ERROR CHECK
    string notBuyableTypes[] = {"Free", "Chance", "GoTo", "Chest", "Tax", "Go"};
    int startIndex = 0, endIndex = 0, separatorCount = 0;
    bool alnumSeen = false;
    string temp;
    for (size_t i = 0; i < propertyData.length(); i++) {
        char c = propertyData.at(i);
        if (c == '|') {
            /// Assign temp to respective variable based on separatorCount
            if (separatorCount == 0) {
                id = stoi(temp);
            }
            else if (separatorCount == 1) {
                name = temp;
            }
            else if (separatorCount == 2) {
                price = stoi(temp);
            }

            /// increment separatorCount
            separatorCount++;
            alnumSeen = false;
        }
        else if (isalnum(c) || c == '-') {
            /// Sets starting index of substring and ending index of substring
            if (!alnumSeen) {
                startIndex = i;
                alnumSeen = true;
            }
            else {
                endIndex = i;
            }
        }

        temp = propertyData.substr(startIndex, endIndex - startIndex + 1);
    }

    if (separatorCount == 3) {
        type = temp;
    }

    buyable = true;
    for (int i = 0; i < 6; i++) {
        if (temp == notBuyableTypes[i]) {
            buyable = false;
            break;
        }
    }

    ownerId = -1;
    upgradeCount = 0;
    // rent = 0;
    rentProgression = {};
}  /// Property

int Property::getId() const {
    return id;
}  /// getId

int Property::getPrice() const {
    return price;
}  /// getPrice

string Property::getName() const {
    return name;
}  /// getName

string Property::getType() const {
    return type;
}  /// getType

int Property::getOwnerId() const {
    return ownerId;
}  /// getOwnerId

void Property::setId(int newId) {
    if (newId > -1) {
        id = newId;
    }
}  /// setId

void Property::setPrice(int newPrice) {
    if (newPrice > -1) {
        price = newPrice;
    }
}  /// setPrice

void Property::setName(string newName) {
    if (!newName.empty()) {
        name = newName;
    }
}  /// setName

void Property::setType(string newType) {
    if (!newType.empty()) {
        type = newType;
    }
}  /// setType

void Property::setOwnerId(int newOwnerId) {
    if (newOwnerId > -1 && ownerId == -1) {
        ownerId = newOwnerId;
    }
}  /// setOwnerId

void Property::removeOwnerId() {
    ownerId = -1;
}  /// removeOwnerId


void Property::setBuyable(bool b) {
        buyable = b;
}

bool Property::isBuyable() {
    return buyable;
}


Property findById(vector<Property> *props, int id) {
    Property fake;
    for (size_t i = 0; i < props->size(); i++) {
        if (props->at(i).getId() == id) {
            return props->at(i);
        }
    }

    return fake;
}

void sortById(vector<Property> &props) {
    for (size_t i = 0; i < props.size() - 1; i++) {
        int minIndex = i;
        for (size_t j = i + 1; j < props.size(); j++) {
            if (props.at(j).id < props.at(minIndex).id) {
                minIndex = j;
            }
        }

        swap(props.at(minIndex), props.at(i));
    }
}

// void Property::setRent(int newRent) {
//     if (newRent > 0) {
//         rent = newRent;
//     }
// }

int Property::getRent() const {
    if (upgradeCount >= rentProgression.size()) {
        return rentProgression.at(rentProgression.size() - 1);
    }
    return rentProgression.at(upgradeCount);
}

bool isUpgradable(const Property &p, const vector<Property> &props) {
    int propTypeOwned = 0;
    for (size_t i = 0; i < props.size(); i++) {
        if (p.type == props.at(i).type) {
            propTypeOwned++;
        }
    }

    // see if all property types are owned
    if (propTypeOwned == 2 && (p.type == "Brown" || p.type == "Blue")) {
        return true;
    }
    else if (propTypeOwned == 3 && (p.type != "Food" || p.type != "Green")) {
        return true;
    }
    else {
        return false;
    }

    // ensure it is not fully upgraded
    if (p.upgradeCount < p.rentProgression.size() - 1) {
        return true;
    }
    else {
        return false;
    }
}

void Property::upgrade() {
    if (upgradeCount >= rentProgression.size() - 1) {
        upgradeCount = rentProgression.size() - 1;
    }
    else {
        upgradeCount++;
    }
}

void setRentProgression(vector<Property> &properties, const vector<vector<int>> &progressions) {
    int progressionCounter = 1;
    for (size_t i = 0; i < properties.size(); i++) {
        if (properties.at(i).buyable && properties.at(i).type != "Food" && properties.at(i).type != "Green") {
            if (progressionCounter < progressions.size()) {
                properties.at(i).rentProgression = progressions.at(progressionCounter);
                progressionCounter++;
            }
        }
        else if (properties.at(i).type == "Green") {
            properties.at(i).rentProgression = progressions.at(0);
        }
    }
}
