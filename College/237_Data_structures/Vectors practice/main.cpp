#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void displayVector(vector<T> v)
{
    for(int i{0}; i < v.capacity(); i++)
    {
        cout << v.at(i) << " ";
    }
    cout << "\n";
}

int main()
{
    vector<int> vect{1,2,3,4,5};
    vector<int> vect2{12,12,12};

    //vect.pop_back();
    //vect.erase(vect.begin());
    //cout << vect.at(0) << '\n';
    //vect.assign(vect2.begin(), vect2.end());
    //vect.insert(vect.begin(), 60);
    cout << vect[0] << "\n";
    displayVector(vect);
}   
