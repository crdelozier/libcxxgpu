#include <list>

#include <cstdlib>
#include <cstdio>
#include <time.h>

#include <cassert>

#define ITERATIONS 5

#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

using namespace std;

int main(int argc, char ** argv){
  long total_time = 0;
  struct timespec start, stop;
  list<DATA_TYPE> int_list;

  unsigned long N = 32000;

  if(argc > 1){
    N = atol(argv[1]);
  }

  for(int i = 0; i < ITERATIONS; i++){

    for(int c = N; c > 0; c--){
      int_list.push_back((DATA_TYPE)(rand() % 500000));
    }

    clock_gettime(CLOCK_REALTIME,&start);

    for(int c = 0; c < ITERATIONS; c++){
      int_list.sort();
    }

    clock_gettime(CLOCK_REALTIME,&stop);
   
    total_time += ((stop.tv_sec-start.tv_sec)*1000000000) + (stop.tv_nsec - start.tv_nsec);

    int_list.clear();
  }

  int val = 0;
  for(std::list<DATA_TYPE>::iterator it = int_list.begin(), e = int_list.end(); it != e; ++it){
    assert(*it >= val);
    val = *it;
  }

  printf("%lu\n", total_time);

  return 0;
}
