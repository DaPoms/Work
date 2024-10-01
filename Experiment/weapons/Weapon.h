//#include <iostream>

// Author: Bohdan D. Jacklitsch
// Creation Date: September 9, 2024
// Filename: Weapon.h
// Purpose: Header of Weapon class
#ifndef WEAPON_H
#define WEAPON_H
using namespace std;
// GLOBAL SPACE, USE WITH CAUTION
// Enum containing different material codes
enum material {none, wood, copper, bronze, iron, steel, adaman};
class Weapon
{
public:
// Constructor
Weapon();
bool operator==(const Weapon& otherWeapon);
// A Second Constructor?
Weapon(string passedName, float passedWeight, int passedPrice, material passedMaterial);
// Copy Constructor
// We will come back to this
Weapon(const Weapon& referenceWeapon);
// Destructor
~Weapon();
// Get and Set for weaponName
string getWeaponName();
void setWeaponName(string passedName);
// Get and Set for legendaryNickname
string getLegendaryNickname();
void setLegendaryNickname(string passedNickname);
// Get and Set for weaponWeight
float getWeaponWeight();
void setWeaponWeight(float passedWeight);
// Get and Set for goldCost
int getGoldCost();
void setGoldCost(int passedCost);
// Get and Set for forgeMaterial
material getForgeMaterial();
void setForgeMaterial(material passedMaterial);
// Converts weapon material into string format
string materialString(material passedMaterial);
// Compare durability to another weapon
int compareDurability(Weapon passedWeapon);
// The following two are good examples of documentation
/**
Name: compareDurability
Description: Compares the durability (material) of the weapon to another
material
Parameters: material passedMaterial - The material to be checked against
Returns: int - negative if the weapon is less durable than the material,
positive if the weapon is more durable than the material,
0 if the weapon is as durable as the material
**/
int compareDurability(material passedMaterial);
/**
Name: pricePerPound
Description: Returns the cost of the weapon (in gold) per pound of weight
Parameters: None
Returns: float - -1 if the weapon weight is 0, otherwise the weapon's
gold cost per pound
**/
float pricePerPound();
// Determines whether another weapon is similar
bool isSimilarWeapon(Weapon passedWeapon);
// Equality Comparison Operator Overload
// We will come back to this
//bool operator==(const Weapon& otherWeapon);
// Print out info about the weapon
void printWeapon();
private:
// Weapon's name
string weaponName;
// Cool heroic name
string legendaryNickname;
// Cost of the weapon in gold pieces
int goldCost;
// Weight of the weapon in pounds
float weaponWeight;
// Material of the weapon
material forgeMaterial;
};
#endif
