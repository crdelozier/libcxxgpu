#include <vector>

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/copy.h>

#include <cstdlib>
#include <cstdio>
#include <time.h>

#include <cassert>

#define ITERATIONS 25

#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

using namespace std;

int main(int argc, char ** argv){
  long total_time = 0;
  struct timespec start, stop;
  vector<DATA_TYPE> int_list;

  unsigned long N = 32000;

  if(argc > 1){
    N = atol(argv[1]);
  }

  for(int i = 0; i < ITERATIONS; i++){

    for(int c = N; c > 0; c--){
      int_list.push_back((DATA_TYPE)(rand() % 500000));
    }

    size_t __total_size = N;
    thrust::device_vector<DATA_TYPE> __device(__total_size);

    clock_gettime(CLOCK_REALTIME,&start);

    thrust::copy(int_list.begin(),int_list.end(),__device.begin());

    clock_gettime(CLOCK_REALTIME,&stop);
 
    thrust::copy(__device.begin(),__device.end(),int_list.begin()); 

    total_time += ((stop.tv_sec-start.tv_sec)*1000000000) + (stop.tv_nsec - start.tv_nsec);

    int_list.clear();
  }

  int val = 0;
  for(std::vector<DATA_TYPE>::iterator it = int_list.begin(), e = int_list.end(); it != e; ++it){
    assert(*it >= val);
    val = *it;
  }

  printf("%lu\n", total_time);

  return 0;
}
