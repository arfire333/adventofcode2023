#include <libaoc.h>
#include <raylib.h>
#include <rlgl.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void getData(istream& in, vector<int64_t>& data) {
  string s;
  while (getline(in, s) && s.size()) {
    data.push_back(atoi(s.c_str()));
  }
}

int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename("2023day05");
  ifstream in(filename);
  vector<int64_t> data;
  getData(in, data);

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