#include <iostream>
#include "BigDecimalInt.h"
using namespace std;
int main() {
    // -321 - (-226) -> -321 + 226 -> 226 - 321
    BigDecimalInt mario("-321"), malak(-226);
    cout << mario - malak << endl;
    return 0;
}