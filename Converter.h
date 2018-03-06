#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <exception>

using namespace std;


class ConvertException : public exception {
public:
    virtual const char *what() = 0;
};

class NotAllowedSymbolException : public ConvertException {
public:
    string msg = "[EXCEPTION] Please enter only allowed symbols.";

    const char *what() {
        return msg.c_str();
    }
};

class BaseOutOfRangeException : public ConvertException {
public:
    string msg = "[EXCEPTION] Base must be smaller than 37 and bigger than 1.";

    const char *what() {
        return msg.c_str();
    }
};

class DigitGreaterThanBaseException : public ConvertException {
public:
    string msg = "[EXCEPTION] Digits may be smaller than base.";

    const char *what() {
        return msg.c_str();
    }
};

class Converter {
private:
    typedef unsigned long ulong;
    typedef unsigned int uint;


    map<int, char> intChar;
    map<char, int> charInt;


    void toUpper(string &str) {
        for (auto &c:str) {
            c = (char) toupper(c);
        }
    }

    bool IsAlphaNum(string number) {
        ulong size = number.size();
        for (int i = 0; i < size; i++) {
            if (!isalnum(number[i])) {
                return false;
            }
        }
        return true;
    }


public:

    Converter() {
        for (int i = 0; i < 26; i++) {
            intChar.insert(pair<int, char>(10 + i, (char) ('A' + i)));
            charInt.insert(pair<char, int>((char) ('A' + i), 10 + i));
        }
        for (int i = 0; i < 10; i++) {
            intChar.insert(pair<int, char>(i, (char) ('0' + i)));
            charInt.insert(pair<char, int>((char) ('0' + i), i));
        }
    }

    uint GetDecNumber(string str, uint base) {
        if (!IsAlphaNum(str))
            throw NotAllowedSymbolException();
        uint dec = 0;
        reverse(str.begin(), str.end());
        for (int i = 0; i < str.size(); i++) {
            if (charInt[str[i]] >= base) {
                throw DigitGreaterThanBaseException();
            }
            dec += charInt[str[i]] * pow(base, i);
        }
        return dec;
    }

    string Convert(const uint decNumber, const uint base) {
        uint div = decNumber;
        string str;

        while (div > 0) {
            string append;
            int remainder = div % base;
            if (remainder >= 10)
                append = intChar[remainder];
            else
                append = to_string(remainder);
            str.append(append);
            div /= base;
        }
        reverse(str.begin(), str.end());
        return str;
    }

};
