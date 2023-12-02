#include <cmath>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <string>
#include <vector>

using namespace std;

string toBinary(uint64_t val, int64_t word_len) {
    stringstream ss;
    while (word_len >= 0) {
        ss << ((val >> word_len--) & 1);
    }
    return ss.str();
}

void getBinaryData(vector<uint64_t> &data, uint64_t &word_len) {
    uint64_t word = 0;
    string s;
    while (cin >> s) {
        word_len = s.size();
        word = 0;
        for (int i = 0; i < word_len; i++) {
            word = word << 1;
            if (s[i] == '1') {
                word += 1;
            }
        }
        data.push_back(word);
    }
}

struct Power {
    int64_t gamma;
    int64_t epsilon;
    int64_t power() { return gamma * epsilon; }
};

struct Power getPower(const vector<uint64_t> &data, const uint64_t word_len) {
    struct Power result = {0};
    vector<uint64_t> ones_counter(64, 0);
    for (int bit = 0; bit < word_len; bit++) {
        for (int word = 0; word < data.size(); word++) {
            ones_counter[bit] += (data[word] & (1 << bit) ? 1 : 0);
        }
    }

    for (int bit = 0; bit < word_len; bit++) {
        if (ones_counter[bit] > data.size() - ones_counter[bit]) {
            result.gamma |= 1 << bit;
        }
    }
    result.epsilon = result.gamma ^ ((1l << word_len) - 1);
    return result;
}

int64_t o2rating(vector<uint64_t> data, uint64_t word_len) {
    vector<bool> keep(data.size(), 1);
    int total = data.size();
    int bit = word_len - 1;
    while (total > 1 && bit >= 0) {
        int zeros = 0;
        int ones = 0;
        int mask = 1 << bit;
        for (int i = 0; i < data.size(); i++) {
            if (keep[i]) {
                if (mask & data[i]) {
                    ones++;
                } else {
                    zeros++;
                }
            }
        }
        int most_common = (ones >= zeros ? 1 : 0);
        for (int i = 0; i < data.size() && total > 1; i++) {
            if (keep[i]) {
                if (((mask & data[i]) > 0) != most_common) {
                    total--;
                    keep[i] = 0;
                }
            }
        }
        bit = bit - 1;
    }
    for (int i = 0; i < data.size(); i++) {
        if (keep[i] == 1) {
            return data[i];
        }
    }
    return -1;
}
int64_t co2rating(vector<uint64_t> data, uint64_t word_len) {
    vector<bool> keep(data.size(), 1);
    int total = data.size();
    int bit = word_len - 1;
    while (total > 1 && bit >= 0) {
        int zeros = 0;
        int ones = 0;
        int mask = 1 << bit;
        for (int i = 0; i < data.size(); i++) {
            if (keep[i]) {
                if (mask & data[i]) {
                    ones++;
                } else {
                    zeros++;
                }
            }
        }
        int least_common = (ones < zeros ? 1 : 0);
        for (int i = 0; i < data.size() && total > 1; i++) {
            if (keep[i]) {
                if (((mask & data[i]) > 0) != least_common) {
                    total--;
                    keep[i] = 0;
                }
            }
        }
        bit = bit - 1;
    }
    for (int i = 0; i < data.size(); i++) {
        if (keep[i] == 1) {
            return data[i];
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    vector<uint64_t> data;
    uint64_t word_len = 0;
    cout << "** Running Binary Diagnostic **\n";
    getBinaryData(data, word_len);
    auto power = getPower(data, word_len);
    cout << "              Gamma: " << power.gamma << "\n";
    cout << "            Epsilon: " << power.epsilon << "\n";
    cout << "  Power Consumption: " << power.power() << "\n";
    auto o2r = o2rating(data, word_len);
    auto co2r = co2rating(data, word_len);
    cout << "          O2 Rating: " << o2r << "\n";
    cout << "         CO2 Rating: " << co2r << "\n";
    cout << "Life support rating: " << o2r * co2r << endl;
    return 0;
}