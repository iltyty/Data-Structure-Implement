#ifndef __PARENTHESIS_MATCH_H_
#define __PARENTHESIS_MATCH_H_

#include <string>
using namespace std;

#include "stack.h"

template <typename T>
bool match(Stack<T> &stack, char ch) {
    if (stack.empty()) {
        return false;
    }
    switch (ch) {
        case ')':
            return stack.top() == '(';
        case ']':
            return stack.top() == '[';
        case '}':
            return stack.top() == '{';
        default:
            return false;
    }
}

bool parenthesis_match(string str) {
    Stack<char> stack;
    for (int i = 0; i < str.length(); i++) {
        switch (str[i]) {
            case '(':
            case '[':
            case '{':
                stack.push(str[i]);
                break;
            case ')':
            case ']':
            case '}':
                if (!match<char>(stack, str[i])) {
                    return false;
                }
                stack.pop();
                break;
            default:
                break;
        }
    }

    return stack.empty();
}

#endif // __PARENTHESIS_MATCH_H_
