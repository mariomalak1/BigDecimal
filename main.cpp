#include <iostream>
#include "BigDecimalInt.h"
using namespace std;
int main() {
    BigDecimalInt mario("1144218"), malak(44127);
//    mario = malak;
//    cout << mario << endl << malak << endl;
    mario = mario + malak;
    cout << "plus operator : " << mario << endl;
    return 0;
}