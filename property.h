#ifndef PROPERTY_H
#define PROPERTY_H
#include <iomanip>
#include <vector>
using namespace std;

class Property {
 public:
    /**
     * Function:    Property
     *              sets to default values for each property
     *
     */
    Property();

    /**
     * Function:    Property
     *              sets the id of the Property with specified value
     *
     * @param newId - id, as an int
     */
    Property(int newId);

    /**
     * Function:    Property
     *              sets all of the member data if Property data is read from a file
     *
     * @param propertyData - string of property data in id|name|price|type format
     */
    Property(string propertyData);

    /**
     * Function:    getId
     *              returns the Property's id
     *
     * @return - id, as an int
     */
    int getId() const;

    /**
     * Function:    getPrice
     *              returns the Property's price
     *
     * @param paramName - paramDescription
     * @return - price, as an int
     */
    int getPrice() const;

    /**
     * Function:    getName
     *              returns the Property's name
     *
     * @return - name, as a string
     */
    string getName() const;

    /**
     * Function:    getType
     *              returns the Property's type
     *
     * @return - type, as a string
     */
    string getType() const;

    /**
     * Function:    getOwnerId
     *              returns the Property's current ownerId
     *
     * @return - ownerId, as an int
     */
    int getOwnerId() const;

    /**
     * Function:    setId
     *              sets the Property id to a value above -1
     *
     * @param newId - the id to set to, as an int
     * @return - void
     */
    void setId(int newId);

    /**
     * Function:    setPrice
     *              sets the Property price to a value above -1
     *
     * @param newPrice - the price to set to, as an int
     * @return - void
     */
    void setPrice(int newPrice);

    /**
     * Function:    setName
     *              sets the Property name to a value above that is not empty
     *
     * @param newName - the name to set to, as an string
     * @return - void
     */
    void setName(string newName);

    /**
     * Function:    setType
     *              sets the Property type to a value above that is not empty
     *
     * @param newType - the type to set to, as an string
     * @return - void
     */
    void setType(string newType);

    /**
     * Function:    setOwnerId
     *              sets the Property ownerId to a value above that is not empty
     *
     * @param newOwnerId - the ownerId to set to, as an int
     * @return - void
     */
    void setOwnerId(int newOwnerId);

    /**
     * Function:    removeOwnerId
     *              remove's the Property's current ownerId resetting it to -1
     *
     * @return - void
     */
    void removeOwnerId();
    
    bool isBuyable();
    void setBuyable(bool b);

    void setRent(int newRent);
    int getRent() const;

    friend Property findById(vector<Property> *props, int id);
    friend void sortById(vector<Property> &props); // helper function for manually assigning properties for testing



 private:
    int id;        /// id of property
    int price;     /// price of property
    string name;   /// name of property
    string type;  /// type of property
    int ownerId;   /// ownerId of property
    bool buyable;
    int rent;
};
#endif