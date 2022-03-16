#include <iostream>
#include <cmath>
#include <chrono>
#include "SHA512.h"
using namespace std::chrono;
using namespace std;

// enc 11.0.0 - CREATED BY RAPIDSLAYER101 (Scott Bree) -- V1-Nonfunctional
const string b64set = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const string b96set = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/¬`!\"£$%^&*()- =[{]};:'@#~\\|,<.>?";

string hex_gens(int n) {
    string res = "";
    for (int i = 0; i < n; i++)
        res += b96set[rand()%96];
    return res;
}

string to_hex(int base_fr, int base_to, string hex_to_convert) {
    cout << hex_to_convert << endl;
    int decimal = 0;
    int power = hex_to_convert.length()-1;
    for (int i = 0; i < hex_to_convert.length(); i++) {
        decimal += powl(b96set.find(hex_to_convert[i])*base_fr, power);
        cout << to_string(pow(b96set.find(hex_to_convert[i])*base_fr, power)) << endl;
        power -= 1;
    }
    cout << decimal << endl;
    string hexadecimal = "";
    while (decimal > 0) {
        hexadecimal = b96set[decimal%base_to]+hexadecimal;
        decimal = floor(decimal/base_to);
    }
    cout << hexadecimal << endl;
    return hexadecimal;
}

string pass_to_seed(string password, string salt){
    SHA512 sha512;
    salt = sha512.hash(sha512.hash(sha512.hash(sha512.hash(salt))+password));
    return to_hex(16, 96, salt);
}

int main() {
    srand(time(NULL));
    auto start = high_resolution_clock::now();
    cout << pass_to_seed("pass", "salt");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;
    return 0;
}
