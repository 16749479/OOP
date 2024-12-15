#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

ostream& upperAndOct(ostream& os) {
    os.setf(ios::oct, ios::basefield); 
    os.unsetf(ios::dec | ios::hex);   
    return os;
}

ostream& hexNoSpaces(ostream& os) {
    os.setf(ios::hex, ios::basefield);
    os.unsetf(ios::dec | ios::oct);    
    return os;
}

bool isNumber(const string& str) {
    for (char ch : str) {
        if (ch < '0' || ch > '9') return false; 
    }
    return !str.empty();
}

bool isAlpha(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool isSpace(char ch) {
    return ch == ' ';
}

void splitInput(const string& input, string words[], int& count) {
    string word;
    count = 0;
    for (char ch : input) {
        if (isSpace(ch)) { 
            if (!word.empty()) {
                words[count++] = word;
                word.clear();
            }
        }
        else {
            word.push_back(ch);
        }
    }
    if (!word.empty()) { 
        words[count++] = word;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    string input;
    cout << "Введите строку: ";
    getline(cin, input);

    const int MAX_WORDS = 100;  
    string words[MAX_WORDS];   
    int count = 0;

    splitInput(input, words, count);

    cout << "Все символы заглавными и числа в OCT формате:" << endl;
    for (int i = 0; i < count; ++i) {
        if (isNumber(words[i])) {
            int number = stoi(words[i]); 
            cout << upperAndOct << number << ' '; 
        }
        else {
            for (char ch : words[i]) {
                if (ch >= 'a' && ch <= 'z') {
                    cout << static_cast<char>(ch - ('a' - 'A')); 
                }
                else {
                    cout << ch; 
                }
            }
            cout << ' '; 
        }
    }
    cout << endl;

    cout << "Строчные буквы и замена пробелов на #:" << endl;
    for (char ch : input) {
        if (ch >= 'A' && ch <= 'Z') {
            cout << static_cast<char>(ch + ('a' - 'A')); 
        }
        else if (isSpace(ch)) {
            cout << '#'; 
        }
        else {
            cout << ch; 
        }
    }
    cout << endl;

   
    cout << "Все числа в HEX формате без пробелов:" << endl;
    for (int i = 0; i < count; ++i) {
        if (isNumber(words[i])) {
            int number = stoi(words[i]); 
            cout << hexNoSpaces << number; 
        }
    }
    cout << endl;

    return 0;
}
