// Author: Bohdan D. Jacklitsch
// Creation Date: September 9, 2024
// Filename: Weapon.cpp
// Purpose: Implementation of Weapon class
#include <iostream>
#include <iomanip>
#include "Weapon.h"
using namespace std;
// Constructor


int main()
{
    Weapon sword{"Bob", 4.21, 520, iron};

    Weapon stick(sword);

    std::cout << sword.pricePerPound();
}

Weapon::Weapon()
{
weaponName = "";
legendaryNickname = "";
weaponWeight = 0;
goldCost = 0;
forgeMaterial = none;
}
// A second constructor?
Weapon::Weapon(string passedName, float passedWeight,
int passedPrice, material passedMaterial)
{
weaponName = passedName;
legendaryNickname = "";
weaponWeight = passedWeight;
goldCost = passedPrice;
forgeMaterial = passedMaterial;
}
// Copy Constructor
// We will come back to this

Weapon::Weapon(const Weapon& referenceWeapon)
{
weaponName = referenceWeapon.weaponName;
legendaryNickname = "";
weaponWeight = referenceWeapon.weaponWeight;
goldCost = referenceWeapon.goldCost;
forgeMaterial = referenceWeapon.forgeMaterial;
}

// Destructor
Weapon::~Weapon()
{}
// SETS AND GETS
string Weapon::getWeaponName() {
return weaponName;
}
void Weapon::setWeaponName(string passedName) {
weaponName = passedName;
}
string Weapon::getLegendaryNickname() {
return legendaryNickname;
}
void Weapon::setLegendaryNickname(string passedNickname) {
legendaryNickname = passedNickname;
}
float Weapon::getWeaponWeight() {
return weaponWeight;
}
void Weapon::setWeaponWeight(float passedWeight) {
weaponWeight = passedWeight;
}
int Weapon::getGoldCost() {
return goldCost;
}
void Weapon::setGoldCost(int passedCost) {
goldCost = passedCost;
}
material Weapon::getForgeMaterial() {
return forgeMaterial;
}
void Weapon::setForgeMaterial(material passedMaterial) {
forgeMaterial = passedMaterial;
}
string Weapon::materialString(material passedMaterial)
{
switch (passedMaterial)
{
case none:
return "None";
case wood:
return "Wood";
case copper:
return "Copper";
case bronze:
return "Bronze";
case iron:
return "Iron";
case steel:
return "Steel";
case adaman:
return "Adamantium";
default:
return "";
}
}
// Compares the duribility of the weapon to a given material
// Negative = less durable, postive = more durable, 0 = as durable
int Weapon::compareDurability(material passedMaterial) {
return (getForgeMaterial() - passedMaterial);
}
// Compares the duribility of the weapon to another weapon
// Negative = less durable, postive = more durable, 0 = as durable
int Weapon::compareDurability(Weapon passedWeapon) {
return (getForgeMaterial() - passedWeapon.getForgeMaterial());
}
// Get the price of the weapon per pound of its weight
float Weapon::pricePerPound() {
return ((weaponWeight != 0) ? goldCost/weaponWeight : -1);
}
// Returns whether the two weapons are similar
bool Weapon::isSimilarWeapon(Weapon passedWeapon)
{
return ( weaponName == passedWeapon.getWeaponName() &&
weaponWeight == passedWeapon.getWeaponWeight() &&
forgeMaterial == passedWeapon.getForgeMaterial() );
}
// Returns whether the two weapons are similar
// We will come back to this

bool Weapon::operator==(const Weapon& otherWeapon)
{
return ( weaponName == otherWeapon.weaponName &&
weaponWeight == otherWeapon.weaponWeight &&
forgeMaterial == otherWeapon.forgeMaterial );
}

// Print the weapon information to the screen

void Weapon::printWeapon()
{
cout << endl;
cout << setw(21) << "Name: " << weaponName << endl;
if (legendaryNickname != "")
{
cout << setw(21) << "Legendary Nickname: " <<
legendaryNickname << endl;
}
cout << setw(21) << "Price: " << goldCost << endl;
cout << setw(21) << "Weight (pounds): " << weaponWeight << endl;
//cout << setw(21) << "Material: " << forgeMaterial << endl;
cout << setw(21) << "Material: " << materialString(forgeMaterial)
<< endl;
}
