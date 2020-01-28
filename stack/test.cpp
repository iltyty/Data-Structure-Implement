#include "stack.h"
#include "conversion.h"
#include "evaluate.h"
#include "parenthesis_match.h"

template <typename T>
void test_stack(int size);
template <typename T>
void test_push(Stack<T> &stack);
template <typename T>
void test_pop(Stack<T> &stack);
template <typename T>
void test_top(Stack<T> &stack);

void test_convert();
void test_parenthesis();
void test_evaluate();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    test_stack<int>(atoi(argv[1]));
    // test_convert();
    // try {
    //     test_parenthesis();
    // } catch (const char *msg) {
    //     cout << msg;
    // }
    test_evaluate();
}

template <typename T>
void test_stack(int size) {
    Stack<int> stack;
    for (int i = 0; i < size; i++) {
        stack.append(rand() % 100);
    }

    test_push(stack);
    test_pop(stack);
    test_top(stack);
}

template <typename T>
void test_push(Stack<T> &stack) {
    cout << "test1 function push" << endl;
    cout << "\tstack(rightmost corresponding to the top): " << stack;
    cout << "\tpush(100): ";
    stack.push(100);
    cout << stack;
}

template <typename T>
void test_pop(Stack<T> &stack) {
    cout << "test2 function pop" << endl;
    cout << "\tstack: " << stack;
    cout << "\tpop(): ";
    stack.pop();
    cout << stack;
}

template <typename T>
void test_top(Stack<T> &stack) {
    cout << "test3 function top" << endl;
    cout << "\tstack: " << stack;
    cout << "\ttop(): " << stack.top() << endl;
}

void test_convert() {
    int n = rand() % 10000;
    cout << "test4 function convert" << endl;
    cout << "\tdecimal number: " << n << endl;
    cout << "\tbinary number: " << convert(n, 2) << endl;
    cout << "\toctal number: " << convert(n, 8) << endl;
    cout << "\thexadecimal number: " << convert(n, 16) << endl;
}

void test_parenthesis() {
    string expr;
    cout << "test5 function parenthesis matching" << endl;
    while (true) {
        cout << "\tinput an expression: ";
        cin >> expr;
        if (expr == "q") {
            return;
        }
        if (parenthesis_match(expr)) {
            cout << "\tlegal" << endl;
        } else {
            cout << "\tillegal" << endl;
        }
    } ;
}

void test_evaluate() {
    char expr[100];
    cout << "test6 function evaluate" << endl;
    while (true) {
        cout << "\tinput an expresssion: ";
        cin.getline(expr, 100);
        if (!strcmp(expr, "q")) {
            return;
        }
        double res = 0;
        try {
            res = evaluate(expr);
        } catch (string msg) {
            cout << "\t" << msg << endl;
        } catch (const char *msg) {
            cout << "\t" << msg << endl;
        }
        cout << "\tresult: " << res << endl;
    }
}
