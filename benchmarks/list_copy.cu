#include <list>

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
  list<DATA_TYPE> int_list;

  unsigned long N = 32000;

  if(argc > 1){
    N = atol(argv[1]);
  }

  for(int i = 0; i < ITERATIONS; i++){

    for(int c = N; c > 0; c--){
      int_list.push_back((DATA_TYPE)(rand() % 500000));
    }

    std::list<DATA_TYPE>::iterator __first = int_list.begin();
    std::list<DATA_TYPE>::iterator __last = int_list.end();
    size_t __total_size = N;
    thrust::device_vector<DATA_TYPE> __device(__total_size);

    // Not provably continuous memory, so use iterators to copy                                                                                                                                                
    thrust::host_vector<DATA_TYPE> __host(__total_size);
    unsigned long __idx = 0;
    for(; __first != __last; ++__first){
      __host[__idx] = *__first;
      ++__idx;
    }
    thrust::copy(__host.begin(),__host.end(),__device.begin());

    clock_gettime(CLOCK_REALTIME,&start);
 
    thrust::copy(__device.begin(),__device.end(),__host.begin());
    __idx = 0;
    for(; __first != __last; ++__first){
      *__first = __host[__idx];
      ++__idx;
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
