#include <vector>
#include <algorithm>

#include <cstdlib>
#include <cstdio>
#include <time.h>

#include <cassert>

#define ITERATIONS 1
#define FINDS 10000

#define M 1046527

#define LINEAR 1
#define BINARY 2

using namespace std;

int main(int argc, char ** argv){
  long total_time = 0;
  struct timespec start, stop;
  std::vector<int> vec;

  unsigned long N = 32000;
  int method = 1;

  if(argc > 1){
    N = atol(argv[1]);
    if(N <= 0){
      printf("N must be greater than 0\n");
      return 1;
    }
  }

  if(argc > 2){
    method = atoi(argv[2]);
    if(method != 1 && method != 2){
      printf("Search method parameters may be 1 (Linear) or 2 (Binary).\n");
      return 1;
    }
  }

  vec.resize(N);
  srand(100);
  unsigned long numFound = 0;

  for(int i = 0; i < ITERATIONS; i++){
    for(int c = 0; c < N; c++){
      vec[c] = rand() % M;
    }

    clock_gettime(CLOCK_REALTIME,&start);

    if(method == LINEAR){
      for(int c = 0; c < FINDS; c++){
        if(find(vec.begin(), vec.end(), rand() % M) != vec.end()){
	  ++numFound;
	}
      }
    }else{
      sort(vec.begin(),vec.end());
      for(int c = 0; c < FINDS; c++){
        if(binary_search(vec.begin(), vec.end(), rand() % M)){
	  ++numFound;
	}
      }
    }

    clock_gettime(CLOCK_REALTIME,&stop);
   
    total_time += ((stop.tv_sec-start.tv_sec)*1000000000) + (stop.tv_nsec - start.tv_nsec);
  }

  printf("%lu ns\n", total_time);

  printf("Found: %lu\n",numFound);

  return 0;
}
