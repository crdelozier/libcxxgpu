#include <list>

#include <cstdio>
#include <time.h>

#define N 100000
#define ITERATIONS 100

using namespace std;

int main(){
  long total_time;
  struct timespec start, stop;
  list<int> int_list;

  for(int c = N - 1; c >= 0; c--){
    int_list.push_back(c);
  }

  clock_gettime(CLOCK_REALTIME,&start);

  for(int c = 0; c < ITERATIONS; c++){
    int_list.sort();
  }

  clock_gettime(CLOCK_REALTIME,&stop);

  total_time = ((stop.tv_sec-start.tv_sec)*1000000000) + (stop.tv_nsec - start.tv_nsec);
  printf("%lu ns\n", total_time);

  return 0;
}
