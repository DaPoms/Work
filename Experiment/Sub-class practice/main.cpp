#include <iostream>
#include "superclass.h"
#include "subclass.h"

using namespace std;

int main()
{
    Sub test{5};

    cout << test.getVal() << '\n';

    cout << test.oneLess();
}
