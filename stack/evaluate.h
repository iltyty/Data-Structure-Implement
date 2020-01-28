#ifndef __EVALUATE_H_
#define __EVALUATE_H_

#include <cmath>
#include <string>
#include <string.h>
using namespace std;

#include "stack.h"
#include "parenthesis_match.h"

const int OPRT_CNT = 9;

const char priority[OPRT_CNT][OPRT_CNT] = {
    // rows: top-of-stack operator
    // columns: current scanned operator

    //         +    -    *    /    !    ^    (    )    \0
    /* + */   '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* - */   '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* * */   '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* / */   '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* ! */   '>', '>', '>', '>', '>', '>', ' ', '>', '>',
    /* ^ */   '>', '>', '>', '>', '<', '>', '<', '>', '>',
    /* ( */   '<', '<', '<', '<', '<', '<', '<', '=', ' ',
    /* ) */   ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    /* 0 */   '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};

int get(char ch) {
    switch (ch) {
        case '+':
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '!':
            return 4;
        case '^':
            return 5;
        case '(':
            return 6;
        case ')':
            return 7;
        case '\0':
            return 8;
        default:
            string msg = "Illegal operator: ";
            msg.push_back(ch);
            throw msg;
    }
}

char get_priority(char ch1, char ch2) {
    return priority[get(ch1)][get(ch2)];
}

bool is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

// Read an operand starting from p
int read_operand(char *&p) {
    int res = 0;
    while (is_digit(*p)) {
        res *= 10;
        res += (*p - '0');
        p++;
    }
    return res;
}

int factorial(int n) {
    if (n < 0) {
        throw "Cannot calculate factorial of negative integer";
    }
    int res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

double calcu(char op, double opnd) {
    if (op == '!') {
        if (!(opnd == (int)opnd)) {
            throw "Cannot calculate factorial of number of double type";
        }

        return factorial((int)opnd);
    } else {
        string msg = "Illegal operator: ";
        msg.push_back(op);
        throw msg;
    }
}

double calcu(char op, double opnd1, double opnd2) {
    switch (op) {
        case '+':
            return opnd1 + opnd2;
            break;
        case '-':
            return opnd1 - opnd2;
            break;
        case '*':
            return opnd1 * opnd2;
            break;
        case '/':
            if (opnd2 == 0) {
                throw "ZeroDivisionError: division by zero";
            }
            return opnd1 / opnd2;
            break;
        case '^':
            return pow(opnd1, opnd2);
            break;
        default:
            string msg = "Illegal operator: ";
            msg.push_back(op);
            throw msg;
    }
}

// Evaluate the value of the infix expression expr
double evaluate(char *p) {
    // Invalid expression
    if (!parenthesis_match(p)) {
        throw "Invalid expression: mismatched parenthesis.";
    }

    int len = strlen(p);
    // Operator stack
    Stack<char> oprt;
    // Operand stack
    Stack<double> opnd;
    oprt.push(0);

    while (!oprt.empty()) {
      if (is_digit(*p)) {
        // Read operand
        int operand = read_operand(p);
        opnd.push(operand);
      } else if (*p == ' ') {
          p++;
      } else {
            char res = get_priority(oprt.top(), *p);
            switch (res) {
                case '<':
                    // Top-of-stack operator has lower priority
                    // Delay the caculation, push the operator
                    oprt.push(*p);
                    p++;
                    break;
                case '>': {
                    // The current operator has lower priority
                    // Calculate and push the result
                    if (opnd.empty()) {
                        string msg = "Illegal expression: ";
                        msg.push_back(oprt.top());
                        msg.push_back(*p);
                        throw msg;
                    }
                    char op = oprt.pop();
                    if (op == '!') {
                        // The unique unary operator
                        double res = calcu(op, opnd.pop());
                        opnd.push(res);
                    } else {
                        double operand2 = opnd.pop();
                        double operand1 = opnd.pop();
                        double res = calcu(op, operand1, operand2);
                        opnd.push(res);
                    }
                    break;
                }
                case '=':
                    p++;
                    oprt.pop();
                    break;
                default:
                    break;
            }
        }
    }

    return opnd.pop();
}

#endif // __EVALUATE_H_
