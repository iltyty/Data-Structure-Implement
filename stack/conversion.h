#ifndef __CONVERSION_H_
#define __CONVERSION_H_

#include<string>

#include"stack.h"

// Conversion between multiple bases
// Args:
//   n: target number
//   base: target base
string convert(int n, int base) {
    if (base < 2 || base > 16) {
        return "";
    }
    Stack<char> stack;
    string digits = "0123456789abcdef";

    do {
        int mod = n % base;
        stack.push(digits[mod]);
        n /= base;
    } while (n);

    string result = "";
    do {
        result += stack.pop();
    } while (!stack.empty());
    return result;
}


#endif // __CONVERSION_H_
