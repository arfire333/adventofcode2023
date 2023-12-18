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

void getData(istream& in, vector<string>& board) {
  string s;
  while (getline(in, s) && s.size()) {
    board.push_back(s);
  }
}

int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0]);
  ifstream in(filename);
  vector<string> data;
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