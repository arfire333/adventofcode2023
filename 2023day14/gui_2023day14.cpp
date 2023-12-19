#include <libaoc.h>
#include <raylib.h>
#include <rlgl.h>
#include <stdint.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const float FONT_SIZE = 24.0;

void getData(istream& in, vector<string>& board) {
  string s;
  while (getline(in, s) && s.size()) {
    replace(s.begin(), s.end(), '.', ' ');
    replace(s.begin(), s.end(), '#', 'k');
    replace(s.begin(), s.end(), 'O', 'C');
    board.emplace_back(s);
  }
}

bool tilt_north(vector<string>& rocks, const vector<string>& blocks) {
  bool moved = false;
  for (int r = 0; r < rocks.size() - 1; r++) {
    for (int c = 0; c < rocks[0].size(); c++) {
      if (rocks[r][c] == ' ' && blocks[r][c] == ' ' && rocks[r + 1][c] != ' ') {
        rocks[r][c] = rocks[r + 1][c];
        rocks[r + 1][c] = ' ';
        moved = true;
      }
    }
  }
  return moved;
}

bool tilt_south(vector<string>& rocks, const vector<string>& blocks) {
  bool moved = false;
  for (int r = rocks.size() - 1; r > 0; r--) {
    for (int c = 0; c < rocks[0].size(); c++) {
      if (rocks[r][c] == ' ' && blocks[r][c] == ' ' && rocks[r - 1][c] != ' ') {
        rocks[r][c] = rocks[r - 1][c];
        rocks[r - 1][c] = ' ';
        moved = true;
      }
    }
  }
  return moved;
}
bool tilt_west(vector<string>& rocks, const vector<string>& blocks) {
  bool moved = false;
  for (int c = 0; c < rocks[0].size() - 1; c++) {
    for (int r = 0; r < rocks.size(); r++) {
      if (rocks[r][c] == ' ' && blocks[r][c] == ' ' && rocks[r][c + 1] != ' ') {
        rocks[r][c] = rocks[r][c + 1];
        rocks[r][c + 1] = ' ';
        moved = true;
      }
    }
  }
  return moved;
}
bool tilt_east(vector<string>& rocks, const vector<string>& blocks) {
  bool moved = false;
  for (int c = rocks[0].size() - 1; c > 0; c--) {
    for (int r = 0; r < rocks.size(); r++) {
      if (rocks[r][c] == ' ' && blocks[r][c] == ' ' && rocks[r][c - 1] != ' ') {
        rocks[r][c] = rocks[r][c - 1];
        rocks[r][c - 1] = ' ';
        moved = true;
      }
    }
  }
  return moved;
}
int64_t north_load(const vector<string>& rocks) {
  int64_t ret = 0;
  for (int r = 0; r < rocks.size(); r++) {
    for (int c = 0; c < rocks[0].size(); c++) {
      if (rocks[r][c] != ' ') {
        ret += rocks.size() - r;
      }
    }
  }
  return ret;
}
int64_t east_load(const vector<string>& rocks) {
  int64_t ret = 0;
  for (int r = 0; r < rocks.size(); r++) {
    for (int c = 0; c < rocks[0].size(); c++) {
      if (rocks[r][c] != ' ') {
        ret += c;
      }
    }
  }
  return ret;
}
int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename("2023day14", "example.input");

  ifstream in(filename);
  vector<string> board;
  getData(in, board);
  vector<string> blocks;
  vector<string> rocks;
  for (const auto& s : board) {
    string rock = s;
    string block = s;
    replace(rock.begin(), rock.end(), 'k', ' ');
    replace(block.begin(), block.end(), 'C', ' ');
    rocks.emplace_back(rock);
    blocks.emplace_back(block);
  }

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(720, 720, argv[0]);
  string fontFilename = aoc::dataFilename("2023day14", "heydings_icons.ttf");
  string fontFilename2 =
      aoc::dataFilename("2023day14", "SpaceMono-Regular.ttf");

  Font block_font = LoadFontEx(fontFilename.c_str(), 72, 0, 0);
  string b(blocks[0].size(), 'k');
  Vector2 line_size = MeasureTextEx(block_font, b.c_str(), FONT_SIZE, 1.0f);
  SetWindowSize(line_size.x, line_size.y * rocks.size());
  SetWindowMinSize(line_size.x, line_size.y * rocks.size());
  SetExitKey(KEY_ESCAPE);
  SetTargetFPS(30);

  stringstream ss;
  int64_t cycles = 0;
  const int64_t TOTAL_CYCLES = 1000000000;
  int64_t spin_count = 0;
  int64_t last_north_load = 0;
  int64_t last_east_load = 0;
  while (!WindowShouldClose()) {
    ClearBackground(BLACK);
    bool moved = true;
    if (cycles < TOTAL_CYCLES) {
      switch (spin_count) {
        case 0:
          moved = tilt_north(rocks, blocks);
          break;
        case 1:
          moved = tilt_west(rocks, blocks);
          break;
        case 2:
          moved = tilt_south(rocks, blocks);
          break;
        default:
          moved = tilt_east(rocks, blocks);
          break;
      }
    }
    BeginDrawing();

    for (int i = 0; i < board.size(); i++) {
      DrawTextEx(block_font, blocks[i].c_str(), {0, line_size.y * i}, FONT_SIZE,
                 1, RED);
      DrawTextEx(block_font, rocks[i].c_str(), {0, line_size.y * i}, FONT_SIZE,
                 1, GREEN);
    }
    int64_t current_north_load = north_load(rocks);
    int64_t current_east_load = north_load(rocks);
    if (!moved) {
      spin_count++;
      spin_count = spin_count % 4;
    }
    if (!moved && spin_count == 0) {
      cycles++;
      last_north_load = current_north_load;
      last_east_load = current_east_load;
    }
    ss.str("");
    ss << "Cycle: " << cycles;
    ss << " Last North Load: " << last_north_load;
    ss << " Last East Load: " << last_east_load;
    ss << " North Load: " << current_north_load;
    ss << " East Load: " << current_east_load;

    // TODO: Finish C++ implementation of fast forwarding. (Originally done in
    // Excel).  In C++, Waited for iterations per spin pattern to reproduce
    // itself printing the sequence with North load.  Length of sequence can
    // likely be found with a lcm. Save the sequence with corresponding loads
    // closest_number_not_over =
    // floor(TOTAL_CYCLES-current_cycle)/pattern_length)*pattern_length+current_cycle
    // increment by 1 until TOTAL_CYCLES reached and read corresponding load

    SetWindowTitle(ss.str().c_str());
    EndDrawing();
  }
  return 0;
}