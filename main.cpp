/* ---------------------------
 Laboratoire : 07
 Fichier : main.cpp
 Auteur(s) : Rochana Pande, Emmanuel Janssens, Robin Demarta
 Date : 05.12.2018

 But : 

 Remarque(s) :

 Compilateur : g++ 6.3.0
 --------------------------- */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string ERROR_MESSAGE = "Non valide";
const int MIN_INT = 1;
const int MAX_INT = 4999;

string convertArabToRoman(string value);
string convertDigitToRoman(char digit, int index);
int convertRomanToArab(string value);
int romanCharToInt(char symbol);
char intToRomanChar(int number);
void displayErrorMessage();

/**
 * @brief 
 * 
 * @return int 
 */
int main() {
    string input;
    int convertedRomanValue;

    while (getline(cin, input) && input != "") {
        int val;
        stringstream ss(input);

        //Try to read value as int
        if (ss >> val) {
            //Convert from arab number to roman
            if (val >= MIN_INT && val <= MAX_INT) {
                cout << convertArabToRoman(to_string(val)) << endl;
            } else {
                displayErrorMessage();
            }
        } else {
            //Convert from roman number to arab
            convertedRomanValue = convertRomanToArab(input);
            if (convertedRomanValue > 0) {
                cout << convertedRomanValue << endl;
            } else {
                displayErrorMessage();
            }
        }
    }
    return 0;
}

/**
 * @brief Displays the error message contained in ERROR_MESSAGE
 * 
 */
void displayErrorMessage() {
    cout << ERROR_MESSAGE << endl;
}

/**
 * @brief Converts an arab number (1-4999) to roman symbols
 * 
 * @param value 
 * @return string 
 */
string convertArabToRoman(string value) {
    string result = "";
    int length = value.length() - 1;
    for (int i = length; i >= 0; --i) {
        result = convertDigitToRoman(value[i], length - i) + result;
    }
    return result;
}

/**
 * @brief Convert one digit of an arab number (1-9) to roman symbol depending
 * 
 * @param digit 
 * @param index position in the number (ex: in 321, 1 is in position 0)
 * @return string 
 */
string convertDigitToRoman(char digit, int index) {
    string result = "";
    int positionMultiplier = 1;

    //Pow
    for (int i = 0; i < index; ++i) {
        positionMultiplier *= 10;
    }

    int intDigit = (digit - '0');  //-> function charToInt()
    int intValue = intDigit * positionMultiplier;

    //Values that compose the digit
    int current = 1 * positionMultiplier;
    int half = 5 * positionMultiplier;
    int next = 10 * positionMultiplier;

    if (intValue < half - positionMultiplier || index == 3) {  //Units
        result.append(intDigit, intToRomanChar(current));      //Adds X times the unit char
    } else if (intValue < half) {                              //IV, XL, CD
        result += intToRomanChar(current);
        result += intToRomanChar(half);
    } else if (intValue == half) {  //V, L or D
        result = intToRomanChar(half);
    } else if (intValue < next - positionMultiplier) {  //VI, VII, VIII, ...
        result += (char)(intToRomanChar(half));
        result.append(intDigit - (half / positionMultiplier), intToRomanChar(current));
    } else {  //IX, XC or CM
        result += intToRomanChar(current);
        result += intToRomanChar(next);
    }

    return result;
}

/**
 * @brief Convert arab number to roman symbol
 * (for basic values only: 1, 10, 50, 100, 500 and 1000)
 * 
 * @param number 
 * @return char 
 */
char intToRomanChar(int number) {
    char result = ' ';
    switch (number) {
        case 1:
            result = 'I';
            break;
        case 5:
            result = 'V';
            break;
        case 10:
            result = 'X';
            break;
        case 50:
            result = 'L';
            break;
        case 100:
            result = 'C';
            break;
        case 500:
            result = 'D';
            break;
        case 1000:
            result = 'M';
            break;
        default:
            break;
    }
    return result;
}

/**
 * @brief Convert a single roman symbol to int value
 * (for basic values only: 1, 10, 50, 100, 500 and 1000)
 * 
 * @param symbol
 * @return int
 */
int romanCharToInt(char symbol) {
    int result = 0;
    switch (symbol) {
        case 'I':
            result = 1;
            break;
        case 'V':
            result = 5;
            break;
        case 'X':
            result = 10;
            break;
        case 'L':
            result = 50;
            break;
        case 'C':
            result = 100;
            break;
        case 'D':
            result = 500;
            break;
        case 'M':
            result = 1000;
            break;
        default:
            break;
    }
    return result;
}

/**
 * @brief Converts a roman number to arab value
 * 
 * @param value (I-MMMMCMXCIX)
 * @return int (1-4999)
 */
int convertRomanToArab(string value) {
    int result = 0;
    int length = value.length() - 1;
    int currentValue;
    int previousValue;
    bool subtract = false;

    for (int i = length; i >= 0; --i) {
        currentValue = romanCharToInt(value[i]);

        if (i < length) {  //Don't check the previous char if it's the first
            previousValue = romanCharToInt(value[i + 1]);
            subtract = currentValue >= previousValue ? false : true;
            result += currentValue * (subtract ? -1 : 1);
        } else {
            result += currentValue;
        }
    }

    //Convert the result value backwards to check conversion validity
    string reverted = convertArabToRoman(to_string(result));
    if (reverted != value) {
        //Incorrect input value
        return 0;
    }

    return result;
}