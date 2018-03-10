//
// Created by e on 09.03.18.
//

#ifndef CONVERTER_H
#define CONVERTER_H

#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <exception>
#include <sstream>
#include <utility>

using namespace std;
namespace exc {
    class ConvertException : public exception {
    public:
        virtual const char *what() = 0;
    };

    class NotAllowedSymbolException : public ConvertException {
    public:
        string msg = "[EXCEPTION] Please enter only allowed symbols.";

        const char *what() override {
            return msg.c_str();
        }
    };

    class EmptyStringException : public ConvertException {
    public:
        string msg = "[EXCEPTION] EmptyStringException.";

        const char *what() override {
            return msg.c_str();
        }
    };

    class DigitGreaterThanBaseException : public ConvertException {
    public:
        string msg = "[EXCEPTION] Digits may be smaller than base.";

        const char *what() override {
            return msg.c_str();
        }
    };
}
using namespace exc;

typedef unsigned int uint;

class Number {
public:
    const string digits;
    const uint base;
    uint intDecPiece; /// merge to long double than modf
    long double fraDecPiece;

    Number(string str, uint bas); //digits(std::move(str)), base(bas)
    string toBase(const uint newBase);

private:
    void split();

    uint getDec(string str);

    long double getDec(string str, bool fra);

    void toUpper(string &str);

    bool isAlphaNum(string number);
};

Number::Number(string str, uint bas) : digits(std::move(str)), base(bas) {
    intDecPiece = 0;
    fraDecPiece = 0;
    if (!isAlphaNum(digits))
        throw NotAllowedSymbolException();
    if (digits.empty())
        throw EmptyStringException();
    split();
}

string Number::toBase(const uint newBase) {
    uint div = intDecPiece;
    stringstream rez;

    while (div > 0) {
        int remainder = div % newBase;
        if (remainder >= 10)
            rez << (char) ('A' + remainder - 10);
        else
            rez << remainder;
        div /= newBase;
    }
    string intPart(rez.str());
    reverse(intPart.begin(), intPart.end());
    rez.str("");

    if (fraDecPiece != 0) {
        long double digit;
        long double tmp = fraDecPiece;
        for (int i = 0; i < 10; i++) {
            if (tmp == 0)
                break;
            tmp = modf(tmp * newBase, &digit);
            rez << static_cast<int>(digit);
        }
        string fraPart(rez.str());

        return intPart + "." + fraPart;
    }
    return intPart;
}

void Number::split() {
    ///////////////////////////////////////////It needs refactor///////////////////////////////////////////////
    std::stringstream intSS;
    std::stringstream fraSS;
    size_t size = digits.size();
    for (int i = 0; i < size; i++) {
        if (digits[i] == '.' || digits[i] == ',') {
            for (int z = i + 1; z < size; z++) {
                fraSS << digits[z];
            }
            break;
        }
        intSS << digits[i];
    }

    intDecPiece = getDec(intSS.str());
    if (!fraSS.str().empty())
        fraDecPiece = getDec(fraSS.str(), true);
}

uint Number::getDec(string str) {
    toUpper(str);
    uint dec = 0;
    reverse(str.begin(), str.end());

    for (uint i = 0; i < str.size(); i++) {
        int tmp;
        if (base > 10)
            tmp = str[i] - 'A' + 10;
        else
            tmp = str[i] - '0';
        if (tmp >= base)
            throw DigitGreaterThanBaseException();
        dec += tmp * pow(base, i);
    }
    return dec;
}

long double Number::getDec(string str, bool fra) {
    toUpper(str);
    long double dec = 0;
    for (int i = -1; i >= -str.size(); i--) {
        int tmp;
        if (base > 10)
            tmp = (str[-(i + 1)] - 'A' + 10);
        else
            tmp = (str[-(i + 1)] - '0');
        if (tmp >= base)
            throw DigitGreaterThanBaseException();
        dec += tmp * pow(base, i);

    }
    return dec;
}

void Number::toUpper(string &str) {
    for (auto &c:str) {
        c = (char) toupper(c);
    }
}

bool Number::isAlphaNum(string number) {
    bool rez = std::all_of(number.begin(), number.end(),
                           [](char c) {
                               if (c == ',' || c == '.')
                                   return true;
                               return (bool)isalnum(c);
                           });
    return rez;

//    ulong size = number.size();
//    for (int i = 0; i < size; i++) {
//        if (number[i] == '.' || number[i] == ',') {
//            continue;
//        }
//        if (!isalnum(number[i])) {
//            return false;
//        }
//    }
//    return true;
}

#endif //CONVERTER_CONVERTER_H
