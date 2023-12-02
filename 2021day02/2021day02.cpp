#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct dir_t {
  int64_t x;
  int64_t y;
  int64_t z;
};

struct dir_t getData(vector<struct dir_t> &in){
  string s;
  int distance;
  struct dir_t net={0};
  while(cin >> s >> distance){
    if( !s.compare("forward") ){
      in.push_back({distance,0,0});
      net.x+=distance;
    }else if( !s.compare("down")){
      in.push_back({0,0,distance});
      net.z+=distance;
    }else if( !s.compare("up")){
      in.push_back({0,0,-distance});
      net.z-=distance;
    }
  }
  cout << net.x << ", " << net.y << ", " << net.z << "\n";
  cout << "Answer: " << net.x * net.z << "\n";
  return net;
}

int main(int argc, char *argv[]){
  vector<struct dir_t> data;
  getData(data);
  cout << "Part 2\n";
  struct dir_t aim={0};
  struct dir_t pos={0};
  for(auto it : data ){
    if( it.x ){
      pos.x+=it.x;
      pos.z+=it.x*aim.z;
    }else {
      aim.z+=it.z;
    }
  }
  cout << pos.x << ", " << pos.y << ", " << pos.z << "\n";
  cout << "Answer: " << pos.x * pos.z << "\n";
  return 0;
}