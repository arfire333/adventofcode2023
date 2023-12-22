#include <libaoc.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
struct dig_t {
  char direction;
  int64_t distance;
  string color;
};
void getData(istream& in, vector<dig_t>& plan) {
  string s;
  while (getline(in, s) && s.size()) {
    dig_t val;
    string buf(10, '\0');
    sscanf(s.c_str(), "%c %ld %s", &val.direction, &val.distance, buf.data());
    val.color = string(buf);
    plan.push_back(val);
  }
}
void correctPlan(vector<dig_t>& plan) {
  for (auto& step : plan) {
    string distance_s = step.color.substr(2, 5);
    sscanf(distance_s.c_str(), "%lx", &step.distance);
    switch (step.color[7]) {
      case '0':
        step.direction = 'R';
        break;
      case '1':
        step.direction = 'D';
        break;
      case '2':
        step.direction = 'L';
        break;
      case '3':
        step.direction = 'U';
        break;
      default:
        break;
    }
  }
}
enum class change {
  RU = (static_cast<int>('R') << 8) + static_cast<int>('U'),
  RD = (static_cast<int>('R') << 8) + static_cast<int>('D'),
  LU = (static_cast<int>('L') << 8) + static_cast<int>('U'),
  LD = (static_cast<int>('L') << 8) + static_cast<int>('D'),
  UR = (static_cast<int>('U') << 8) + static_cast<int>('R'),
  UL = (static_cast<int>('U') << 8) + static_cast<int>('L'),
  DR = (static_cast<int>('D') << 8) + static_cast<int>('R'),
  DL = (static_cast<int>('D') << 8) + static_cast<int>('L')
};
bool clockwise(const vector<dig_t>& plan) {
  // assume clockwise
  int l = 0;
  int r = 0;
  for (auto i = 1; i < plan.size(); i++) {
    auto dirchange = static_cast<change>(
        (static_cast<int>(plan[i - 1].direction) << 8) + plan[i].direction);
    switch (dirchange) {
      case change::LU:
        r++;
        break;
      case change::LD:
        l++;
        break;
      case change::RU:
        l++;
        break;
      case change::RD:
        r++;
        break;
      case change::UR:
        r++;
        break;
      case change::UL:
        l++;
        break;
      case change::DR:
        l++;
        break;
      case change::DL:
        r++;
        break;
    }
  }
  return r > l;
}
pair<int64_t, int64_t> getLineEnd(const dig_t& curr_step,
                                  const dig_t& next_step,
                                  bool clockwise,
                                  int64_t& r,
                                  int64_t& c) {
  auto dirchange = static_cast<change>(
      (static_cast<int>(curr_step.direction) << 8) + next_step.direction);
  int mod = 0;
  switch (dirchange) {
    case change::LU:
      mod = (clockwise ? 2 : 1);
      c -= curr_step.distance;
      break;
    case change::LD:
      mod = (clockwise ? 3 : 0);
      c -= curr_step.distance;
      break;
    case change::RU:
      mod = (clockwise ? 0 : 3);
      c += curr_step.distance;
      break;
    case change::RD:
      mod = (clockwise ? 1 : 2);
      c += curr_step.distance;
      break;
    case change::UR:
      mod = (clockwise ? 0 : 3);
      r -= curr_step.distance;
      break;
    case change::UL:
      mod = (clockwise ? 2 : 1);
      r -= curr_step.distance;
      break;
    case change::DR:
      mod = (clockwise ? 1 : 2);
      r += curr_step.distance;
      break;
    case change::DL:
      mod = (clockwise ? 3 : 0);
      r += curr_step.distance;
      break;
  }
  int64_t vc = c;
  int64_t vr = r;
  switch (mod) {
    case 1:
      vc += 1;
      break;
    case 2:
      vr += 1;
      break;
    case 3:
      vr += 1;
      vc++;
      break;
    default:
      break;
  }
  return {vr, vc};
}
void getVertices(const vector<dig_t>& plan,
                 bool clockwise,
                 vector<pair<int64_t, int64_t>>& vertices) {
  vertices.push_back({0, 0});
  int64_t r = 0;
  int64_t c = 0;
  for (auto i = 0; i < plan.size(); i++) {
    auto j = (i + 1) % plan.size();
    vertices.push_back(getLineEnd(plan[i], plan[j], clockwise, r, c));
  }
  vertices[0] = vertices.back();
}
int64_t calcArea(vector<pair<int64_t, int64_t>>& vertices) {
  int64_t sum = 0;
  for (size_t i = 0; i < vertices.size() - 1; i++) {
    auto xi = vertices[i].second;
    auto xip1 = vertices[i + 1].second;
    auto yi = vertices[i].first;
    auto yip1 = vertices[i + 1].first;
    sum += (xi * yip1 - xip1 * yi - xi * yi + xip1 * yip1);
    printf(
        "(%ld,%ld)->(%ld,%ld) => (%ld * %ld - %ld * %ld) = %ld  sum = "
        "%ld\n",
        xi, yi, xip1, yip1, xi, yip1, xip1, yi, (xi * yip1 - xip1 * yi), sum);
  }
  sum = (sum < 0 ? -sum : sum);

  return sum / 2;
}
#ifndef EXCLUDE_MAIN
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "user.input");
  ifstream in(filename);
  vector<dig_t> plan;
  getData(in, plan);
  vector<pair<int64_t, int64_t>> vertices;
  bool clock = clockwise(plan);
  cout << "Clockwise? " << (clock ? "Yes" : "No") << "\n";
  getVertices(plan, clock, vertices);
  int64_t answer = calcArea(vertices);
  cout << "Part 1 Answer is: " << answer << "\n";
  correctPlan(plan);
  clock = clockwise(plan);
  vertices.clear();
  getVertices(plan, clock, vertices);
  answer = calcArea(vertices);
  cout << "Part 2 Answer is: " << answer << "\n";

  return 0;
}
#endif