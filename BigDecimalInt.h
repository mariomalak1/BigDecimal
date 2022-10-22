/*
* class BigDecimalInt
        * Assignment 1 OOP / Dr. ElRamly
        * created by:
*      Mario Malak  --> id : 20210313
*      Aya Mohamed  --> id : 20211020
*      Islam Ahmed  --> id : 2021
* created on : 2022/10/5
*/

#ifndef STRINGVERSION_BIGDECIMAL_H
#define STRINGVERSION_BIGDECIMAL_H

#include <iostream>
#include <regex>

using namespace std;

class BigDecimalInt {
private:
    string arrchar; // vector of chars to hold the digits of the big number
    int signNumber{}; // value equal 0 if it negative, 1 if it positive
    BigDecimalInt(){}
public:
    BigDecimalInt(string number);
    BigDecimalInt(int number);

    // member function that return the addition of two objects of the class
    BigDecimalInt operator+ (BigDecimalInt anotherDec); // arithmetic operator

    // member function to check  that two big decimal object are the same
    bool operator==(const BigDecimalInt& Dec1);     // logic operator

    // member function to check that is this object is greater than the second object
    bool operator> (const BigDecimalInt& Dec1);     // logic operator

    // friend function to make the first big decimal object is the same to the another object
    BigDecimalInt operator= (const BigDecimalInt &Dec1);  // assignment operator

    // operator to print the BigDecimalInt object
    friend ostream& operator << (ostream& out, BigDecimalInt b);  // bitwise operator

    // return size of the object in bits
    int size();

    // return sign of number
    char sign();
};

BigDecimalInt::BigDecimalInt(string number){
    int i = 0;
    //check if number is valid or not
    regex validOrNot("((\\+?)[0-9]+)|((\\-){1}[0-9]+)");
    //if input is invalid exit program .
    if (!regex_match(number, validOrNot)) {
        cerr << "This number is invalid , Please enter a valid number .";
        exit(0);
    }
    if (number[0] == '-'){
        signNumber = 0;
        i++;
    }else if(number[0] == '+') {
        signNumber = 1;
        i++;
    }else {
        signNumber = 1;
    }
    while(number[i] == '0'){
        i++;
        continue;
    }for(; i < number.length(); i++){
        arrchar += number[i];
    }
} // done

BigDecimalInt::BigDecimalInt(int number){
    // reject it if it equals to 1274675999 as it the biggest number can the data type integer have,
    // so it can make calculation error
    if (number >= 1274675999){
        cerr << "enter number is more than or equal 1274675999 in string not integer" << endl;
        exit(-1274675999);
    }
    if(number < 0){
        signNumber = 0;
        number *= -1;
    }else {
        signNumber = 1;
    }
    this->arrchar = to_string(number);
}

bool BigDecimalInt::operator==(const BigDecimalInt& Dec1){
    if ( arrchar == Dec1.arrchar and signNumber == Dec1.signNumber){
        return true;
    }else{
        return false;
    }
}

// must remove all zeroes if the number has in the first
bool BigDecimalInt::operator> (const BigDecimalInt& Dec1){
    if ( arrchar.length() == Dec1.arrchar.length()){
        int index = 0;
        if (arrchar == Dec1.arrchar){
            return false;
        }else{
            checkAgian:
            if (index == arrchar.length()){
                return true;
            }
            cout << "after flag" << endl;
            if (arrchar[index] == Dec1.arrchar[index]){
                index++;
                goto checkAgian;
            }
            else if (int (arrchar[index] - 48) > int(Dec1.arrchar[index] - 48)){
                return true;
            }
            else {
                return false;
            }
        }
    }
    else if(arrchar.length() > Dec1.arrchar.length()){
        return true;
    }
    else{
        return false;
    }
} // done

BigDecimalInt BigDecimalInt::operator=(const BigDecimalInt &Dec1) {
    BigDecimalInt Dec2;
    this->arrchar = Dec1.arrchar;
    this->signNumber = Dec1.signNumber;
    return Dec2;
}

ostream& operator << (ostream& out, BigDecimalInt Dec){
    if (Dec.signNumber == 0){
        out << "-";
    }
    for (int i = 0; i < Dec.arrchar.length(); ++i) {
        out << int(Dec.arrchar[i] - 48);
    }
    return out;
}

int BigDecimalInt::size() {
    return arrchar.length();
}

char BigDecimalInt::sign() {
    if (signNumber == 0){
        return 43;
    }else{
        return 45;
    }
}

BigDecimalInt BigDecimalInt :: operator+ (BigDecimalInt anotherDec){
    BigDecimalInt answer;
    int ans = 0, carry = 0;

    // if two decimals are equal in length and sign
    if(arrchar.length() == anotherDec.arrchar.length() && signNumber == anotherDec.signNumber){
        for(int i = arrchar.length() - 1; i >= 0; i--){
            ans = (int(arrchar[i] - 48)) + (int(anotherDec.arrchar[i] - 48)) + carry;
            cout << arrchar[i] - 48 << " + " << anotherDec.arrchar[i] - 48 << " + " << carry << endl;
            if(ans > 9){
                carry += 1;
                ans -= 10;
            }else{
                carry = 0;
            }
            answer.arrchar += to_string(ans);
            ans = 0;
        }
        if(carry == 1){
            answer.arrchar += to_string(carry);
        }
        answer.signNumber = signNumber;
    }

    // if one decimal is bigger than the second decimal and are equal in sign
    if (arrchar.length() > anotherDec.arrchar.length() && signNumber == anotherDec.signNumber) {
        int i = anotherDec.arrchar.length() - 1;
        int j = arrchar.length() - 1;
        for (; i >= 0; i--) {
            ans = (int (arrchar[j] - 48)) + (int (anotherDec.arrchar[i] - 48)) + carry;
            cout << arrchar[j] - 48 << " + " << anotherDec.arrchar[i] - 48 << " + " << carry << endl;
            if (ans > 9) {
                carry = 1;
                ans -= 10;
                cout << "answer after -10 : " << ans << endl;
            } else {
                carry = 0;
            }
            answer.arrchar += to_string(ans);
            ans = 0;
        }
        i = arrchar.length() - anotherDec.arrchar.length() - 1;
        if (carry == 1) {
            answer.arrchar += to_string(carry + int (arrchar[i] - 48) );
            i--;
        }
        for (; i >= 0; --i) {
            answer.arrchar += int(arrchar[i] - 48);
        }
        answer.signNumber = signNumber;
    }

    // if one decimal is bigger than the second decimal and are equal in sign
    else if (anotherDec.arrchar.length() > arrchar.length() && signNumber == anotherDec.signNumber) {
        int i = arrchar.length() - 1;
        for (; i >= 0; i--) {
            ans = (int (arrchar[i] - 48)) + (int (anotherDec.arrchar[i] - 48)) + carry;
            if (ans > 9) {
                carry = 1;
                ans -= 10;
            } else {
                carry = 0;
            }
            answer.arrchar += to_string(ans);
            ans = 0;
        }
        i = anotherDec.arrchar.length() - arrchar.length() - 1;
        if (carry == 1) {
            answer.arrchar += to_string(carry + int (anotherDec.arrchar[i] - 48));
            i--;
        }
        for (; i >= 0; --i) {
            answer.arrchar += (anotherDec.arrchar[i] - 48);
        }
        answer.signNumber = signNumber;
    }

    reverse(answer.arrchar.begin(), answer.arrchar.end());
    return answer;
}

#endif //STRINGVERSION_BIGDECIMAL_H