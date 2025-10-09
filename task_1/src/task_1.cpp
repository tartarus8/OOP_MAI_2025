#include <iostream>
using namespace std;

typedef enum {
    OK = 0,
    WRONG_INPUT = 1
} error_codes;

error_codes zero_to_nine(int input) {
    switch (input) {
        case 0: cout << "sıfır";  return OK;
        case 1: cout << "bir";  return OK;
        case 2: cout << "iki";  return OK;
        case 3: cout << "üç";  return OK;
        case 4: cout << "dört";  return OK;
        case 5: cout << "beş";  return OK;
        case 6: cout << "altı";  return OK;
        case 7: cout << "yedi";  return OK;
        case 8: cout << "sekiz";  return OK;
        case 9: cout << "dokuz";  return OK;
        default: {
            cerr << "error: input isn't a supported digit";
            return WRONG_INPUT;
        }
    }
}

error_codes decades(int input) {
    switch (input) {
        case 1: cout << "on";  return OK;
        case 2: cout << "yirmi";  return OK;
        case 3: cout << "otuz";  return OK;
        case 4: cout << "kırk";  return OK;
        case 5: cout << "elli";  return OK;
        case 6: cout << "altmış";  return OK;
        case 7: cout << "yetmiş";  return OK;
        case 8: cout << "seksen";  return OK;
        case 9: cout << "doksan";  return OK;
        default: {
            cerr << "error: input isn't a supported digit";
            return WRONG_INPUT;
        }
    }
}

int main() {
    int input;
    cin >> input;
    if (input < 0 || input > 99) {
        cerr << "error: input isn't a supported number";
        return WRONG_INPUT;
    }

    if (input < 10) {
        zero_to_nine(input);
    } else if (input % 10 == 0) {
        decades(input / 10);
    } else {
        decades(input / 10);
        cout << ' ';
        zero_to_nine(input % 10);
    }
    return 0;
}
