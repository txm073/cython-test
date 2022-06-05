#include <string>
#include <cstring>
#include <iostream>


extern "C" {
    int length(char* str) {
        int len = 0;
        while (*(str + len)) {
            len++;
        }
        return len;
    }

    char* reverseString(char* str) {
        std::string _reversed = "";
        int len = (int)length(str);
        for (int i = len - 1; i > -1; --i) {
            _reversed += str[i];
        }
        char* reversed = strdup(_reversed.c_str());
        return reversed;
    }

    std::string returnString(std::string str) {
        return str;
    }

    int mult(int a, int b) {
        return a * b;
    }
}

int main(int argc, char** argv) {
    std::cout << argc << "\n";
    std::cout << reverseString(argv[0]) << "\n";
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << "\n";
    }
    return 0;
}
