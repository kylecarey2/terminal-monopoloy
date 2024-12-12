#include "property.h"

#include <cstdlib>

Property::Property() {
    id = -1;
    price = -1;
    name = "-";
    type = "-";
    ownerId = -1;
}  /// Property

Property::Property(int newId) {
    if (newId > -1) {
        id = newId;
    }
}  /// Property

Property::Property(string propertyData) {
    // id|name|price|type
    /// DOES NOT ERROR CHECK
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

    ownerId = -1;
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


