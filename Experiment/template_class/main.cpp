#include <iostream>
using namespace std;

template<typename T>
class Test
{
    private:
    T thing;

    public:
    Test(T passed) : thing{passed}{}

    void addAndPrint(T passed)
    {
        cout << thing + passed;
    }

};

int main()
{
    Test t(3);
    t.addAndPrint(4);
}
