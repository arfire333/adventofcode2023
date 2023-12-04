#include <raylib.h>
#include <rlgl.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void getData(vector<int64_t>& in) {
  string s;
  while (getline(cin, s)) {
    if (s.size() != 0) {
      in.push_back(atoi(s.c_str()));
    }
  }
}

int main(int argc, char* argv[]) {
  vector<int64_t> data;
  getData(data);

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, argv[0]);
  SetExitKey(KEY_ESCAPE);
  SetTargetFPS(30);

  stringstream ss;
  while (!WindowShouldClose()) {
    BeginDrawing();
    for (int i = 0; i < data.size(); i++) {
      ss.str("");
      ss << data[i];
      DrawText(ss.str().c_str(), 0, 20 * i, 24, WHITE);
    }
    EndDrawing();
  }
  return 0;
}