#include <iostream>
#include "BigDecimalInt.h"
using namespace std;
int main() {
    BigDecimalInt mario("318"), malak(127);
//    cout << (mario < malak) << endl;
    cout << mario - malak << endl;
    return 0;
}