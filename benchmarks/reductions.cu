#include <vector>
#include <algorithm>

#include <cstdlib>
#include <cstdio>
#include <time.h>

#include <cassert>

#define ITERATIONS 5

using namespace std;

#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

int main(int argc, char ** argv){
  long total_time = 0;
  struct timespec start, stop;
  vector<DATA_TYPE> int_vector;

  unsigned long N = 32000;

  DATA_TYPE sum1 = 0;
  DATA_TYPE sum2 = 0;

  if(argc > 1){
    N = atol(argv[1]);
  }

  for(int i = 0; i < ITERATIONS; i++){

    for(int c = N; c > 0; c--){
      int_vector.push_back((DATA_TYPE)(rand() % 500000));
    }

    clock_gettime(CLOCK_REALTIME,&start);

    for(int c = 0; c < ITERATIONS; c++){
      sum1 += *min_element(int_vector.begin(),int_vector.end());
      sum2 += *max_element(int_vector.begin(),int_vector.end());
    }

    clock_gettime(CLOCK_REALTIME,&stop);
   
    total_time += ((stop.tv_sec-start.tv_sec)*1000000000) + (stop.tv_nsec - start.tv_nsec);

    int_vector.clear();
  }

  assert(sum1 != sum2);

  printf("%lu\n", total_time);

  return 0;
}
