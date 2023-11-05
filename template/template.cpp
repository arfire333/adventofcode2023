#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int64_t return1(){ return 1; }

void getData(vector<int64_t> &in){
  string s;
  while(getline(cin, s)){
    if( s.size()!=0 ){
      in.push_back(atoi(s.c_str()));
    }
  }
}

#ifndef EXCLUDE_MAIN
int main(int argc, char *argv[]){
  vector<int64_t> data;
  getData(data);
  for( auto it : data ){
    cout << it << "\n";
  }

  return 0;
}
#endif