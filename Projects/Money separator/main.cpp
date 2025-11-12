#include <iostream>

int totalTobillscoins(int x, int cash) // Separates user's money by whatever specified currency value is put in for x, but in cents (EX: 100 = 1 USD)
{
    std::cout << cash / x << " " << x / 100.0 << " dollar bills.\n";

    return cash % x;
}


void currencySeparate(int cash) //Works up to 100 dollar bills, coins referenced in proportion to a dollar (Ex: .05 dollar = nickel)
{
   
    std::cout << "You get:\n";
    cash = totalTobillscoins(10000,cash);
    cash = totalTobillscoins(1000,cash);
    cash = totalTobillscoins(100,cash);
    cash = totalTobillscoins(25,cash);
    cash = totalTobillscoins(10,cash);
    cash = totalTobillscoins(5,cash);
    totalTobillscoins(1,cash);
}


int main()
{
    double money{};
    std::cout << "How much $ do you have?: ";
    std::cin >> money;

    currencySeparate(money * 100 + .001); //Add .001 to balance out float imprecision without actually impacting the # 

}
