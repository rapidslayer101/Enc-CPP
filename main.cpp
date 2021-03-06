#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <chrono>
#include "SHA512.h"

using namespace std::chrono;
using namespace std;

// this project aims to recreate enc 11.8.0's enclib.py in c++ for faster efficiency
// enc++ 0.2.0 - CREATED BY RAPIDSLAYER101 (Scott Bree) -- V1-Nonfunctional
SHA512 sha512; //instantiate a SHA512 object
const string _b94set_ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/`!\"$%^&*() -=[{]};:'@#~\\|,<.>?";
const string _b96set_ = _b94set_+"¬£";

string rand_b96_str(int n) {
    string res = "";
    for (int i = 0; i < n; i++)
        res += _b96set_[rand()%96];
    return res;
}

//string to_hex(int base_fr, int base_to, string hex_to_convert) {
//    cout << hex_to_convert << endl;
//    int decimal = 0;
//    int power = hex_to_convert.length()-1;
//    for (int i = 0; i < hex_to_convert.length(); i++) {
//        decimal += powl(b96set.find(hex_to_convert[i])*base_fr, power);
//        cout << to_string(pow(b96set.find(hex_to_convert[i])*base_fr, power)) << endl;
//        power -= 1;
//    }
//    cout << decimal << endl;
//    string hexadecimal = "";
//    while (decimal > 0) {
//        hexadecimal = b96set[decimal%base_to]+hexadecimal;
//        decimal = floor(decimal/base_to);
//    }
//    cout << hexadecimal << endl;
//    return hexadecimal;
//}

string pass_to_key(string password, string salt, int depth){
    for (int i = 0; i < depth; i++)
        password = sha512.hash(password+salt);
    return password;
}

string _xor_(string data, string key, string xor_salt) {
    string key_value = "";
    for (int i = 0; i < floor(data.length()/64)+1; i++) {
        key = sha512.hash(key+xor_salt);
        key_value += key;
    }
    cout << "\n" << key_value.length() << endl;
}

int main() {
    string data = rand_b96_str(10000);
    srand(time(NULL));
    string key = pass_to_key("hello world", "salt", 100000);
    cout << key;
    auto start = high_resolution_clock::now();
    _xor_(data, key, "salt");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\n" << duration.count()/1000000.f << " Seconds" << endl;
    return 0;
}