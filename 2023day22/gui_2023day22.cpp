#include <libaoc.h>
#include <raylib.h>
#include <rlgl.h>
#include <stdint.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const vector<Color> COLORS = {{255, 0, 0, 255}, {255, 255, 0, 255},
                              {0, 255, 0, 255}, {0, 255, 255, 255},
                              {0, 0, 255, 255}, {255, 0, 255, 255}};

struct brick_t {
  Vector3 position;
  Vector3 shape;
  Color c;

  brick_t() = default;
  brick_t(const Vector3& p, const Vector3& s) : position(p), shape(s){};
  friend bool operator<(const brick_t& l, const brick_t& r) {
    return l.position.z < r.position.z;
  }
  friend ostream& operator<<(ostream& os, const brick_t& l) {
    os << "(" << l.position.x - l.shape.x / 2 << ", "
       << l.position.y - l.shape.y / 2 << ", " << l.position.z - l.shape.z / 2
       << ")-(" << l.position.x + l.shape.x / 2 << ", "
       << l.position.y + l.shape.y / 2 << ", " << l.position.z + l.shape.z / 2
       << ")";
    return os;
  }
};
Vector3 getData(istream& in, vector<brick_t>& bricks) {
  string s;
  Vector3 max_all = {0};
  brick_t desert_floor;
  desert_floor.position.x = 0;
  desert_floor.position.y = 0;
  desert_floor.position.z = .5;
  desert_floor.shape.x = 100;
  desert_floor.shape.y = 100;
  desert_floor.shape.z = 1;
  bricks.push_back(desert_floor);
  int i = 0;
  while (getline(in, s) && s.size()) {
    brick_t brick;

    sscanf(s.c_str(), "%f,%f,%f~%f,%f,%f", &brick.position.x, &brick.position.y,
           &brick.position.z, &brick.shape.x, &brick.shape.y, &brick.shape.z);
    if (brick.shape.x > max_all.x) {
      max_all.x = brick.shape.x;
    }
    if (brick.shape.y > max_all.y) {
      max_all.y = brick.shape.y;
    }
    if (brick.shape.z > max_all.z) {
      max_all.z = brick.shape.z;
    }
    brick.shape.x = brick.shape.x - brick.position.x + 1;
    brick.shape.y = brick.shape.y - brick.position.y + 1;
    brick.shape.z = brick.shape.z - brick.position.z + 1;
    brick.position.x = brick.position.x + brick.shape.x / 2;
    brick.position.y = brick.position.y + brick.shape.y / 2;
    brick.position.z = brick.position.z + brick.shape.z / 2;
    brick.c = COLORS[i++];
    bricks.emplace_back(brick);
    i = i % COLORS.size();
  }
  max_all.x++;
  max_all.y++;
  max_all.z++;
  return max_all;
}
bool overlap_xy(const brick_t& l, const brick_t& r) {
  float lxl = l.position.x - l.shape.x / 2;
  float lxr = l.position.x + l.shape.x / 2;
  float lyl = l.position.y - l.shape.y / 2;
  float lyr = l.position.y + l.shape.y / 2;
  float rxl = r.position.x - r.shape.x / 2;
  float rxr = r.position.x + r.shape.x / 2;
  float ryl = r.position.y - r.shape.y / 2;
  float ryr = r.position.y + r.shape.y / 2;
  if (lxl >= rxr || lxr <= rxl) {
    return false;
  }
  if (lyl >= ryr || lyr <= ryl) {
    return false;
  }
  return true;
}
/**
 * Returns true if supporter is supporting supported.
 */
bool is_supporting(const brick_t& supporter, const brick_t& supported) {
  if (!overlap_xy(supporter, supported)) {
    return false;
  }
  int supporter_top = lroundf(supporter.position.z + supporter.shape.z / 2);
  int supported_bottom = lroundf(supported.position.z - supported.shape.z / 2);
  if (supporter_top == supported_bottom) {
    return true;
  }
  return false;
}
bool is_above(const brick_t& l, const brick_t& r) {
  float lzl = l.position.z - l.shape.z / 2;
  float rzr = r.position.z + r.shape.z / 2;
  if (lzl >= rzr) {
    return true;
  }
  return false;
}

bool can_fall(const brick_t& l, const brick_t& r) {
  float lzl = l.position.z - l.shape.z / 2 - 1;
  float rzr = r.position.z + r.shape.z / 3;
  if (lzl >= rzr) {
    return true;
  }
  return false;
}

bool updateBricks(vector<brick_t>& bricks) {
  bool changed = !is_sorted(bricks.begin() + 1, bricks.end());
  sort(bricks.begin() + 1, bricks.end());
  for (auto i = 1; i < bricks.size(); i++) {
    bool drop = true;
    for (auto j = i - 1; j >= 0; j--) {
      if (!overlap_xy(bricks[i], bricks[j])) {
        continue;
      }
      if (!can_fall(bricks[i], bricks[j])) {
        drop = false;
      }
    }
    if (drop) {
      bricks[i].position.z--;
      changed = true;
    }
  }
  return changed;
}
size_t doPart1(vector<brick_t>& bricks) {
  vector<vector<size_t>> supporting(bricks.size(), vector<size_t>());
  vector<vector<size_t>> supportedby(bricks.size(), vector<size_t>());
  for (auto i = 1; i < bricks.size(); i++) {
    cout << bricks[i] << " is supporting ";
    for (auto j = i + 1; j < bricks.size(); j++) {
      if (is_supporting(bricks[i], bricks[j])) {
        supporting[i].push_back(j);
        supportedby[j].push_back(i);
        cout << bricks[j] << " ";
      }
    }
    cout << "\n";
  }
  vector<size_t> can_remove;
  for (auto i = 1; i < supporting.size(); i++) {
    bool remove_it = true;
    for (auto supported : supporting[i]) {
      if (supportedby[supported].size() == 1) {
        remove_it = false;
        break;
      }
    }
    if (remove_it) {
      can_remove.push_back(i);
    }
  }
  return can_remove.size();
}
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename("2023day22", "user.input");
  ifstream in(filename);
  vector<brick_t> bricks;
  Vector3 max_all = getData(in, bricks);

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(200, 800, argv[0]);
  SetExitKey(KEY_ESCAPE);
  Camera3D camera = {0};
  camera.position = {0.0f, max_all.z * 3 / 2,
                     max_all.z / 2};   // Camera position
  camera.position = {50.0f, 50, -50};  // Camera position
  camera.target = {max_all.x / 2, max_all.y / 2,
                   max_all.z / 8};  // Camera looking at point
  camera.up = {0.0f, 0.0f, 1.0f};  // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;  // Camera mode type
  SetTargetFPS(60);
  brick_t reference_brick;
  reference_brick.position.x = max_all.x / 2;
  reference_brick.position.y = max_all.y / 2;
  reference_brick.position.z = .5;
  reference_brick.shape.x = max_all.x;
  reference_brick.shape.y = max_all.y;
  reference_brick.shape.z = 1;

  bool last_changed = true;
  bool keypressed = false;
  bool part1done = false;

  stringstream ss;
  string status = "Press a key to start.";
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE)) {
      keypressed = true;
      ss.str("");
      ss << "Bricks are still falling.";
      status = ss.str();
    }
    if (keypressed && last_changed) {
      last_changed = updateBricks(bricks);
    }
    if (!last_changed && !part1done) {
      size_t safe_to_remove = doPart1(bricks);
      part1done = true;
      ss.str("");
      ss << safe_to_remove << " bricks can be disintegrated.";
      status = ss.str();
    }

    UpdateCamera(&camera, CAMERA_ORBITAL);

    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(camera);
    size_t color_idx = 0;
    DrawCubeWiresV(reference_brick.position, reference_brick.shape,
                   {245, 235, 225, 255});
    for (auto i = 1; i < bricks.size(); i++) {
      auto brick = bricks[i];
      DrawCubeV(brick.position, brick.shape, brick.c);
      color_idx = color_idx % COLORS.size();
    }
    EndMode3D();
    int height = GetScreenHeight();
    DrawText(status.c_str(), 5, height - 20, 20, WHITE);
    EndDrawing();
  }
  return 0;
}