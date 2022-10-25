#include <iostream>
#include "BigDecimalInt.h"
using namespace std;
int main() {
    BigDecimalInt mario("188"), malak(2899);
    cout << mario + malak << endl;
    cout << mario - malak << endl;
    return 0;
}