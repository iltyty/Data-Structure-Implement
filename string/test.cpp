#include <iostream>
using namespace std;

#include "string.h"

const int LEN = 94;

const char alphabet[LEN] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', '`', '~', '!', '@', '#', '$', '%', '^',
    '&', '*', '(', ')', '-', '+', '_', '=', '{', '}', '[', ']', '\\', '|',
    ';', ':', '\'', '"', ',', '<', '>', '.', '?', '/',
};

void test_string(int size);
void test_operator_add(String &str, int size);
void test_substr(String &str);
void test_prefix(String &str);
void test_suffix(String &str);
void test_concat(String &str);
void test_equal(String &str);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    test_string(atoi(argv[1]));
    return 0;
}

void test_string(int size) {
    srand(time(0));
    String str;

    test_operator_add(str, size);
    test_substr(str);
    test_prefix(str);
    test_suffix(str);
    test_concat(str);
    test_equal(str);
}

void test_operator_add(String &str, int size) {
    cout << "test1 operator +=" << endl;
    cout << "before add: " << str << "after add ";
    for (int i = 0; i < size; i++) {
        int r = rand() % LEN;
        cout << alphabet[r];
        str += alphabet[r];
    }
    cout << ": " << endl <<  str << endl;
}

void test_substr(String &str) {
    String sub1 = str.substr(0, 5);
    String sub2 = str.substr(5, 4);
    cout << "test2 substring" << endl;
    cout << "substr(0, 5): " << sub1;
    cout << "substr(5, 4): " << sub2 << endl;
}

void test_prefix(String &str) {
    String pre1 = str.prefix(0);
    String pre2 = str.prefix(5);
    String pre3 = str.prefix(10);
    String pre4 = str.prefix(str.length());
    cout << "test3 prefix" << endl;
    cout << "prefix(0)" << pre1;
    cout << "prefix(5)" << pre2;
    cout << "prefix(10)" << pre3;
    cout << "prefix(" << str.length() << ")" << pre3 << endl;
}

void test_suffix(String &str) {
    String suf1 = str.suffix(0);
    String suf2 = str.suffix(5);
    String suf3 = str.suffix(10);
    String suf4 = str.suffix(str.length());
    cout << "test4 suffix" << endl;
    cout << "suffix(0)" << suf1;
    cout << "suffix(5)" << suf2;
    cout << "suffix(10)" << suf3;
    cout << "suffix(" << str.length() << ")" << suf3 << endl;
}

void test_concat(String &str) {
    String str1("", 0);
    String str2("123", 3);
    cout << "test5 concat" << endl;
    str.concat(str1);
    cout << "concat \"\"(empty string): " << str;
    str.concat(str2);
    cout << "concat \"123\": " << str;
}

void test_equal(String &str) {
    String str1("123", 3);
    String str2 = str;
    bool flag1 = str.equal(str1);
    bool flag2 = str.equal(str2);
    cout << "test6 equal" << endl;
    cout << str << "==" << str1 << ": " << (flag1 ? "true" : "false");
    cout << str << "==" << str2 << ": " << (flag2 ? "true" : "false");
}
