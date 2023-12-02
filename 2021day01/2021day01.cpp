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
  int64_t last=data[0];
  int64_t greater=0;
  for( int i=1; i<data.size(); i++ ){
    if( data[i] > last ) greater++;
    last = data[i];
  }
  std::cout << greater << " readings were greater than the previous one.\n";
  float lastsum=data[0]+data[1]+data[2];
  greater=0;
  float sum=0;
  for( int i=3; i<data.size(); i++ ){
    sum=data[i]+data[i-1]+data[i-2];
    if( sum > lastsum ) greater++;
    lastsum = sum;
  }
  std::cout << greater << " average readings were greater than the previous average.\n";
  return 0;
}
#endif