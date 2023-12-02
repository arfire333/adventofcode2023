#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct draw {
  int16_t red;
  int16_t green;
  int16_t blue;
};

void getData(vector<vector<draw>> &in){
  string s;
  while(getline(cin, s)){
    int64_t count=0;
    char color=0;
    int64_t front=0;
    int64_t back=0; 
    vector<draw> current_game;
    draw current_draw;
    do { 
        back=s.find_first_of(",;*",front);
        auto sub=s.substr(front,back);
        sscanf(sub.c_str(),"%ld %c",&count,&color); 
        switch( color ){
          case 'r':
            current_draw.red=count;
            break;
          case 'g':
            current_draw.green=count;
            break;
          case 'b':
            current_draw.blue=count;
            break;
        } 
        if( s[back]!=',' ){
          current_game.push_back(current_draw);
          current_draw.blue=0;
          current_draw.red=0;
          current_draw.green=0;
        }
        front=back+1;
    } while ( s[back]!='*' );
    in.push_back(current_game);
  }
}

#ifndef EXCLUDE_MAIN
int main(int argc, char *argv[]){
  vector<vector<draw>> data;
  getData(data);

  int64_t id=0;
  int64_t sum=0;
  int64_t power_sum=0;
  for(auto game : data ){
    id++;
    int64_t red=0;
    int64_t green=0;
    int64_t blue=0;
    int64_t power=0;
    for(auto draw : game ){
      red=( red > draw.red ? red : draw.red );
      blue=( blue > draw.blue ? blue : draw.blue );
      green=( green > draw.green ? green : draw.green );
    }
    power_sum+=red*blue*green;
    if( red<=12 && blue <=14 && green <= 13 ){
      sum+=id;
    }
  }
  cout << "sum: " << sum << "\n";
  cout << "power_sum: " << power_sum << "\n";
  return 0;
}
#endif