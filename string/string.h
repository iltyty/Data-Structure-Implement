#ifndef __STRING_H_
#define __STRING_H_

#include "../vector/vector.h"

class String: public Vector<char> {
    public:
        String() {}
        String(const char *str, int len);
        String(const String &str);
        String(char *elem, Rank low, Rank high);

        int length();
        char char_at(Rank i);
        String substr(Rank i, Rank k);
        String prefix(Rank k);
        String suffix(Rank k);
        void concat(String str);
        bool equal(String str);

        String& operator += (String str);
        String& operator += (char ch);
        friend ostream& operator << (ostream &os, String &str) {
            for (int i = 0; i < str.length(); i++) {
                cout << str._elem[i];
            }
            cout << endl;
            return os;
        }
};

String::String(char *elem, Rank low, Rank high) {
    if (high <= low) {
        _capacity = DEFAULT_CAPACITY;
        _elem = new char[_capacity];
        _size = 0;
    }
    this->copy_from(elem, low, high);
}

String::String(const char *str, int len) {
    this->copy_from(str, 0, len);
}

String::String(const String &str) {
    this->copy_from(str._elem, 0, str._size);
}

int String::length() { return this->_size; }

char String::char_at(Rank i) { return this->_elem[i]; }

// Return substring of length k starting from position i
String String::substr(Rank i, Rank k) {
    return String(this->_elem, i, i + k);
}

String String::prefix(Rank k) {
    return substr(0, k);
}

String String::suffix(Rank k) {
    return substr(this->_size - k, k);
}

void String::concat(String str) {
    for (int i = 0; i < str.length(); i++) {
        this->append(str[i]);
    }
}

bool String::equal(String str) {
    if (this->_size != str.length()) {
        return false;
    }

    for (int i = 0; i < this->_size; i++) {
        if (this->_elem[i] != str[i]) {
            return false;
        }
    }

    return true;
}

String& String::operator += (String str) {
    concat(str);
    return *this;
}

String& String::operator += (char ch) {
    this->append(ch);
    return *this;
}

#endif // __STRING_H_
