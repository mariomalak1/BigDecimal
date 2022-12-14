/*
* class BigDecimalInt
        * Assignment 1 OOP / Dr. ElRamly
        * created by:
*      Mario Malak  --> id : 20210313
*      Aya Mohamed  --> id : 20211020
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
    int signNumber; // value equal 0 if it negative, 1 if it positive

    // empty constructor
    BigDecimalInt(){
        arrchar = "";
        signNumber = 1;
    }

    // function to get 9's complement of the object
    void nine_s_complement(BigDecimalInt &dec1){
        string anotherArr = "";
        for (int i = 0; i < dec1.arrchar.length(); ++i) {
            anotherArr += to_string(9 - int(dec1.arrchar[i] - 48));
        }
        dec1.arrchar = anotherArr;
    }

    // function that complete the decimal number with zeroes to be in length with the biggest number
    void completeWithZeroes(string &arr, int lengthBigOne){
        lengthBigOne = lengthBigOne - arr.length();
        string newDec = "";
        for (int i = 0; i < lengthBigOne; ++i) {
            newDec += '0';
        }
        newDec += arr;
        arr = newDec;
    }

    // function to delete all zeroes in the first of the object if founded
    void RemoveZeroes(string &arr){
        if (arr[0] == '0' and arr.length() > 1) {
            int i = 0;
            string number = arr;
            arr = "";
            while (number[i] == '0') {
                i++;
                continue;
            }
            for (; i < number.length(); i++) {
                arr += number[i];
            }
        }
    }

public:
    BigDecimalInt(string number);
    BigDecimalInt(int number);

    // member function that return the addition of two objects of the class
    BigDecimalInt operator+ (BigDecimalInt anotherDec); // arithmetic operator

    // member function that return the subtraction of two objects of the class
    BigDecimalInt operator- (BigDecimalInt anotherDec); // arithmetic operator

    // member function to check  that two big decimal object are the same
    bool operator==(const BigDecimalInt& Dec1);     // logic operator

    // member function to check that is this object is greater than the second object
    bool operator> (const BigDecimalInt& Dec1);     // logic operator

    // member function to check that is this object is greater than the second object
    bool operator< (BigDecimalInt &anotherDec);      // logic operator

    // friend function to make the first big decimal object is the same to the another object
    BigDecimalInt &operator= (const BigDecimalInt &Dec1);  // assignment operator

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
    if (this->signNumber == Dec1.signNumber) {
        if (arrchar.length() == Dec1.arrchar.length()) {
            int index = 0;
            if (arrchar == Dec1.arrchar) {
                return false;
            } else {
                checkAgian:
                if (index == arrchar.length()) {
                    return true;
                }
                if (arrchar[index] == Dec1.arrchar[index]) {
                    index++;
                    goto checkAgian;
                } else if (int(arrchar[index] - 48) > int(Dec1.arrchar[index] - 48)) {
                    return true;
                } else {
                    return false;
                }
            }
        } else if (arrchar.length() > Dec1.arrchar.length()) {
            return true;
        } else {
            return false;
        }
    }
    // if sign is not the same
    else{
        if (this->signNumber == 1 and Dec1.signNumber == 0){
            return true;
        }else{
            return false;
        }
    }
} // done

bool BigDecimalInt::operator< (BigDecimalInt &anotherDec){
    BigDecimalInt newDecimal;
    newDecimal.arrchar = arrchar;
    newDecimal.signNumber = signNumber;
    if (newDecimal == anotherDec){
        return false;
    } else if(newDecimal > anotherDec){
        return false;
    }else{
        return true;
    }
}

BigDecimalInt &BigDecimalInt::operator=(const BigDecimalInt &Dec1) {
    BigDecimalInt Dec2;
    this->arrchar = Dec1.arrchar;
    this->signNumber = Dec1.signNumber;
    return Dec2;
}

ostream& operator << (ostream& out, BigDecimalInt Dec){
    if (Dec.arrchar == ""){
        out << 0;
    }
    else if (Dec.arrchar[0] == 0){
        out << 0;
    }else {
        if (Dec.signNumber == 0) {
            out << "-";
        }
        for (int i = 0; i < Dec.arrchar.length(); ++i) {
            out << int(Dec.arrchar[i] - 48);
        }
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
        answer.signNumber = anotherDec.signNumber;
        for(int i = arrchar.length() - 1; i >= 0; i--){
            ans = (int(arrchar[i] - 48)) + (int(anotherDec.arrchar[i] - 48)) + carry;
            if(ans > 9){
                carry = 1;
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
    if (arrchar.length() > anotherDec.arrchar.length() && signNumber == anotherDec.signNumber){
        answer.signNumber = anotherDec.signNumber;
        int i = anotherDec.arrchar.length() - 1;
        int j = arrchar.length() - 1;
        for (; i >= 0; i--, j--) {
            ans = (int (arrchar[j] - 48)) + (int (anotherDec.arrchar[i] - 48)) + carry;
            if (ans > 9) {
                carry = 1;
                ans -= 10;
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
            answer.arrchar += int(arrchar[i]);
        }
        answer.signNumber = signNumber;
    }

    // if one decimal is bigger than the second decimal and are equal in sign
    else if (anotherDec.arrchar.length() > arrchar.length() && signNumber == anotherDec.signNumber) {
        answer.signNumber = anotherDec.signNumber;
        int i = arrchar.length() - 1;
        int j = anotherDec.arrchar.length() - 1;
        for (; i >= 0; i--, j--) {
            ans = (int (arrchar[i] - 48)) + (int (anotherDec.arrchar[j] - 48)) + carry;
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
            answer.arrchar += (anotherDec.arrchar[i]);
        }
        answer.signNumber = signNumber;
    }

    // if the second number is negative, then flip the operation to subtraction
    // ex: 465 + (-321) = 465 - 321
    else if (anotherDec.signNumber == 0 and signNumber == 1){
        anotherDec.signNumber = 1;
        return (*this) - anotherDec;
    }

    // if the first number is negative, then flip the operation to subtraction
    // ex: -465 + 321 = 321 - 465
    else if (anotherDec.signNumber == 1 and signNumber == 0){
        this->signNumber = 1;
        return anotherDec - (*this);
    }

    reverse(answer.arrchar.begin(), answer.arrchar.end());
    return answer;
}

BigDecimalInt BigDecimalInt :: operator- (BigDecimalInt anotherDec){
    BigDecimalInt answer;

    // if the second number is negative make this as plus operation
    if (anotherDec.signNumber == 0){
        anotherDec.signNumber = 1;
        return (*this) + anotherDec;
    } else if (signNumber == 0 and anotherDec.signNumber == 1){
        signNumber = 1;
        answer = *this + anotherDec;
        answer.signNumber = 0;
        return answer;
    }else {

        // complete the difference between length of the objects with zeroes
        if (anotherDec.arrchar.length() > arrchar.length()) {
            completeWithZeroes(arrchar, anotherDec.arrchar.length());
        }
        // complete the difference between length of the objects with zeroes
        else if (arrchar.length() > anotherDec.arrchar.length()) {
            completeWithZeroes(anotherDec.arrchar, arrchar.length());
        }

        // get the 9's complement of the second number and plus it with the second number
        nine_s_complement(anotherDec);
        answer = (*this) + anotherDec;


        // remove carry number and add it this number again
        if (answer.arrchar.length() == anotherDec.arrchar.length() + 1){
            string newArr = "";
            // object that has the first digit only
            BigDecimalInt objFirstDigit;
            objFirstDigit.arrchar = to_string(answer.arrchar[0] - 48);
            for (int i = 1; i < answer.arrchar.length(); ++i) {
                newArr += answer.arrchar[i];
            }
            answer.arrchar = newArr;
            answer = objFirstDigit + answer;
            RemoveZeroes(answer.arrchar);
            return answer;
        }

        // this number is negative as no carry up from it
        else if (answer.arrchar.length() == anotherDec.arrchar.length()){
            answer.signNumber = 0;
            nine_s_complement(answer);
            RemoveZeroes(answer.arrchar);
            return answer;
        }
    }
}
#endif //STRINGVERSION_BIGDECIMAL_H
