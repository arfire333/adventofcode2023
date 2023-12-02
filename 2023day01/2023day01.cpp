#include <iostream>
#include <map>
#include <sstream>
#include <stdint.h>
#include <string>
#include <vector>

using namespace std;

int64_t return1() { return 1; }

const map<string, int8_t> word2int = {
    {"one", 1},   {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6},
    {"seven", 7}, {"eight", 8}, {"nine", 9}
};

int16_t firstDigit(const string s) {
    for (auto i = 0; i < s.size(); i++) {
        auto c = s[i];
        if (c >= '0' && c <= '9') {
            return i;
        }
    }
    return -1;
}

int16_t lastDigit(const string s) {
    for (int16_t i = s.size(); i >= 0; i--) {
        auto c = s[i];
        if (c >= '0' && c <= '9') {
            return i;
        }
    }
    return -1;
}

int16_t get_value_part1(const string s) {
    int16_t f=firstDigit(s);
    int16_t l=lastDigit(s);
    if( f < 0 || l < 0 ) return 0;
    int16_t result = (s[f]-'0')*10 + s[l]-'0';
    return result; 
}

int16_t get_value_part2(const string s) {
    int16_t min_idx = firstDigit(s);
    int16_t min_idx_val = ( min_idx>=0 ? s[min_idx]-'0' : 0 );
    if ( min_idx < 0 ) min_idx=INT16_MAX;
    int16_t max_idx = lastDigit(s);
    int16_t max_idx_val = ( max_idx>=0 ? s[max_idx]-'0' : 0 );
    for (auto it = word2int.begin(); it != word2int.end(); it++) {
        int16_t fpos = s.find(it->first);
        int16_t lpos = s.rfind(it->first);
        if (fpos >= 0 && fpos <= min_idx) {
            min_idx = fpos;
            min_idx_val = it->second;
        }
        if (lpos >= 0 && lpos >= max_idx) {
            max_idx = lpos;
            max_idx_val = it->second;
        }
    }
    return min_idx_val*10 + max_idx_val;
}

void getData(vector<int64_t> &d1, vector<int64_t> &d2) {
    string s;

    while (getline(cin, s)) {
        if (s.size() != 0) {
          d1.push_back(get_value_part1(s));
          d2.push_back(get_value_part2(s));
        }
    }
}

#ifndef EXCLUDE_MAIN
int main(int argc, char *argv[]) {
    vector<int64_t> d1, d2;
    getData(d1,d2);
    int64_t sum1 = 0;
    int64_t sum2 = 0;

    for (auto i=0; i<d1.size(); i++){
        sum1 += d1[i];
        sum2 += d2[i];
    }
    cout << sum1<< "\n";
    cout << sum2<< "\n";

    return 0;
}
#endif