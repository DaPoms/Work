#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void displayVector(vector<T> v)
{
    for(int i{0}; i < v.capacity(); i++) //prints everything, including empty space, I could use v.size() to only print actual elements of the vector
    {
        cout << v.at(i) << " ";
    }
    cout << "\n";
}

int main()
{
    vector<char> vect{'Q','U','I','T'};
    vector<char> vect2{'2','1','1'};

    //vect.pop_back();
    //vect.erase(vect.begin() + 1); Erases index 1, the 2nd element
    //vect.erase(vect.begin()); //Erases index 0, the 1st element
    //vect.insert(vect.begin() + 4,'E');
    //cout << vect.at(4) << '\n';
    //vect.assign(vect2.begin(), vect2.end());
    vect.insert(vect.begin() + 4, 'E');
    cout << vect[0] << "\n";
    displayVector(vect);
}   
