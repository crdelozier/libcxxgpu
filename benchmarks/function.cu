#include <vector>
#include <algorithm>

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <time.h>

#include <cassert>

#define ITERATIONS 5

#define M 50

using namespace std;

#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

struct Foo{
  __host__ __device__ DATA_TYPE operator() (DATA_TYPE i){
    for(int c = 0; c < M; c++){
      i += 5;
      //i /= 3;
      //i += 2;
      //i *= 11;
      //i /= 7;
      //i *= 10;
      //i += 2;
    }

    return i; 
  }
} myobject;

int main(int argc, char ** argv){
  long total_time = 0;
  struct timespec start, stop;
  vector<DATA_TYPE> int_vector;

  DATA_TYPE lastVal = 0;

  unsigned long N = 32000;

  if(argc > 1){
    N = atol(argv[1]);
  }

  for(int i = 0; i < ITERATIONS; i++){
    int_vector.clear();

    for(int c = N; c > 0; c--){
      int_vector.push_back((DATA_TYPE)(rand() % 500000));
    }

    lastVal = int_vector[0];

    clock_gettime(CLOCK_REALTIME,&start);

    for(int c = 0; c < ITERATIONS; c++){
      std::transform(int_vector.begin(),int_vector.end(),int_vector.begin(),myobject);
    }

    clock_gettime(CLOCK_REALTIME,&stop);

    total_time += ((stop.tv_sec-start.tv_sec)*1000000000) + (stop.tv_nsec - start.tv_nsec);
  }

  assert(lastVal != int_vector[0]);

  printf("%lu\n", total_time);

  return 0;
}
