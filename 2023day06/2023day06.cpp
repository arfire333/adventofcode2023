#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef EXCLUDE_MAIN
int64_t winners(const vector<int64_t>& time,
                const vector<int64_t>& best_distance) {
  vector<int64_t> pwin;
  for (int i = 0; i < time.size(); i++) {
    int64_t winners = 0;
    for (int speed = 0; speed < time[i]; speed++) {
      int64_t distance = (time[i] - speed) * speed;
      if (distance > best_distance[i]) {
        winners++;
      }
    }
    pwin.push_back(winners);
  }
  int64_t product = 1;
  for (auto win : pwin) {
    product *= win;
  }
  return product;
}

int main(int argc, char* argv[]) {
  vector<int64_t> time = {48, 98, 90, 83};
  vector<int64_t> best_distance = {390, 1103, 1112, 1360};
  auto part1 = winners(time, best_distance);
  cout << "part 1 score: " << part1 << "\n";
  time = {48989083};
  best_distance = {390110311121360};
  auto part2 = winners(time, best_distance);
  cout << "part 2 score: " << part2 << "\n";

  return 0;
}
#endif