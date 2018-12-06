#include <iostream>
#include <string>

using namespace std;

const char DEFAULT_CHAR = ' ';

/*
    Robin
*/
string convertArabToRoman(string value);
/*
    Robin
*/
string convertDigitToRoman(char digit, int index);

char getRomanChar(int number);

/*
    Rochana/emmanuel
*/
string checkConversionType(string entry);
/*
    Rochana/Emmanuel
*/
string convertRomanToArab(string value);

/*
    Rochana/emmanuel
*/
int getArabNumber(char roman);

int main() {
    string input;
    while (getline(cin, input) && input != "") {
        cout << convertArabToRoman(input) << endl;
    }
    return 0;
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

    if (intValue < half - positionMultiplier || index == 3) { //Units
        result.append(intDigit, getRomanChar(current)); //Adds X times the unit char
    } else if (intValue < half) { //IV, XL, CD
        result += getRomanChar(current);
        result += getRomanChar(half);
    } else if (intValue == half) { //V, L or D
        result = getRomanChar(half);
    } else if (intValue < next - positionMultiplier) {  //VI, VII, VIII, ...
        result += (char)(getRomanChar(half));
        result.append(intDigit - (half / positionMultiplier), getRomanChar(current));
    } else {  //IX, XC or CM
        result += getRomanChar(current);
        result += getRomanChar(next);
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
char getRomanChar(int number) {
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