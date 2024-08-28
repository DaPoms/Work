#include <iostream>
#include <string>
#include <string_view>

std::string getName(int num) 
{
	std::string name{};
	std::cout << "Enter the name of person " << num << ": ";
	std::getline(std::cin >> std::ws, name); //std::ws removes whitespace, getline allows reading past whitespaces

	return name;
}

int getAge(std::string_view name)
{
	int age{};
	std::cout << "Enter the age of " << name << ": ";
	std::cin >> age;
	return age;
}

void compareAge(std::string_view name1, std::string_view name2, int age1, int age2)
{
	if (age1 > age2)
		std::cout << name1 << " (age " << age1 << ") is older than " << name2 << " (age " << age2 << ".";

	else	
		std::cout << name2 << " (age " << age2 << ") is older than " << name1 << " (age " << age1 << ").";
}

int main()
{
	system("CLS");

	std::string_view name1{getName(1)};
	int age1{getAge(name1)};
	std::string_view name2{getName(2)};
	int age2{getAge(name2)};
	
	compareAge(name1, name2, age1, age2);
}

