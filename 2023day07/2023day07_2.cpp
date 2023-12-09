#include <libaoc.h>
#include <stdint.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

class Hand {
 public:
  enum struct HAND_TYPES {
    UNKNOWN = 0,
    FIVE = 7,
    FOUR = 6,
    FULL = 5,
    THREE = 4,
    TWO = 3,
    ONE = 2,
    HIGH = 1
  };

  Hand(string const& cards, int64_t bet) : _bet(bet), _cards(cards) { type(); };
  friend ostream& operator<<(ostream& os, const Hand& hand) {
    os << hand._cards << " " << hand._bet;
    return os;
  }

  friend bool operator<(const Hand& l, const Hand& r) {
    return tie(l.hand_type, CARD_STRENGTH[l._cards[0]],
               CARD_STRENGTH[l._cards[1]], CARD_STRENGTH[l._cards[2]],
               CARD_STRENGTH[l._cards[3]], CARD_STRENGTH[l._cards[4]]) <
           tie(r.hand_type, CARD_STRENGTH[r._cards[0]],
               CARD_STRENGTH[r._cards[1]], CARD_STRENGTH[r._cards[2]],
               CARD_STRENGTH[r._cards[3]], CARD_STRENGTH[r._cards[4]]);
  }
  int64_t bet() const { return _bet; }
  string cards() const { return _cards; }
  HAND_TYPES type() {
    if (hand_type != HAND_TYPES::UNKNOWN) {
      return hand_type;
    }
    vector<int8_t> count(CARD_STRENGTH.size(), 0);
    for (auto card : _cards) {
      if (card == 'J') {
        for (auto& c : count) {
          c++;
        }
      } else {
        count[CARD_STRENGTH[card]]++;
      }
    }
    vector<int8_t> has(6, 0);
    for (auto it : count) {
      has[it]++;
    }
    if (has[5]) {
      hand_type = HAND_TYPES::FIVE;
    } else if (has[4]) {
      hand_type = HAND_TYPES::FOUR;
    } else if (has[3] == 1 && has[2] == 1 || has[3] == 2) {
      hand_type = HAND_TYPES::FULL;
    } else if (has[3]) {
      hand_type = HAND_TYPES::THREE;
    } else if (has[2] == 2) {
      hand_type = HAND_TYPES::TWO;
    } else if (has[2]) {
      hand_type = HAND_TYPES::ONE;
    } else {
      hand_type = HAND_TYPES::HIGH;
    }

    return hand_type;
  }

 private:
  int64_t _bet;
  std::string _cards;
  static map<const char, int8_t> CARD_STRENGTH;
  HAND_TYPES hand_type = HAND_TYPES::UNKNOWN;
};

map<const char, int8_t> Hand::CARD_STRENGTH = {
    {'J', 0}, {'2', 1}, {'3', 2}, {'4', 3},  {'5', 4},  {'6', 5}, {'7', 6},
    {'8', 7}, {'9', 8}, {'T', 9}, {'Q', 10}, {'K', 11}, {'A', 12}};

void getData(istream& in, vector<Hand>& hands) {
  string s;
  while (getline(in, s) && s.size()) {
    size_t split = s.find_first_of(" ");
    string bet_s = s.substr(split, string::npos);
    int64_t bet = strtoll(bet_s.c_str(), nullptr, 10);
    string hand = s.substr(0, split);
    hands.emplace_back(hand, bet);
  }
}

#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename("2023day07", "example.input");
  filename = aoc::dataFilename("2023day07", "user.input");
  ifstream in(filename);
  vector<Hand> hands;
  getData(in, hands);

  sort(hands.begin(), hands.end());
  int64_t winnings = 0;
  int64_t rank = 1;
  for (auto const& hand : hands) {
    winnings += hand.bet() * rank;
    cout << hand.cards() << " " << rank << " " << hand.bet()
         << " total=" << winnings << "\n";
    rank++;
  }
  cout << "Winnings=" << winnings << "\n";

  return 0;
}
#endif