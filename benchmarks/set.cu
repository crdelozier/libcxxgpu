#include <vector>
#include <algorithm>

#include <cstdlib>
#include <cstdio>
#include <time.h>

#include <cassert>

#define ITERATIONS 5
#define OPERATION 2

using namespace std;

#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

int main(int argc, char ** argv){
  long total_time = 0;
  struct timespec start, stop;
  vector<DATA_TYPE> set1;
  vector<DATA_TYPE> set2;

  unsigned long N = 32000;

  if(argc > 1){
    N = atol(argv[1]);
  }


#if OPERATION == 1
  vector<DATA_TYPE> output(N * 2);
#else
  vector<DATA_TYPE> output(N);
#endif

  for(int i = 0; i < ITERATIONS; i++){

    for(int c = N; c > 0; c--){
      set1.push_back((DATA_TYPE)(rand() % 500000));
      set2.push_back((DATA_TYPE)(rand() % 500000));
    }

    sort(set1.begin(),set1.end());
    sort(set2.begin(),set2.end());

    bool noCopy = false;

    for(int c = 0; c < ITERATIONS; c++){
      switch(OPERATION){
      case 1:
        clock_gettime(CLOCK_REALTIME,&start);
        set_union(set1.begin(),set1.end(),
		  set2.begin(),set2.end(),
                  output.begin(),noCopy);
        
        clock_gettime(CLOCK_REALTIME,&stop);
        total_time += ((stop.tv_sec-start.tv_sec)*1000000000) + (stop.tv_nsec - start.tv_nsec);
	break;
      case 2:
        clock_gettime(CLOCK_REALTIME,&start);
        set_intersection(set1.begin(),set1.end(),
			 set2.begin(),set2.end(),
			 output.begin(),noCopy);
        clock_gettime(CLOCK_REALTIME,&stop);
        total_time += ((stop.tv_sec-start.tv_sec)*1000000000) + (stop.tv_nsec - start.tv_nsec);
        for(vector<DATA_TYPE>::iterator it = output.begin(), e = output.begin() + 2; it != e; ++it){
          assert(find(set1.begin(),set1.end(),*it) != set1.end());
	}
	break;
      case 3:
        clock_gettime(CLOCK_REALTIME,&start);
	set_difference(set1.begin(),set1.end(),
		       set2.begin(),set2.end(),
		       output.begin());
        clock_gettime(CLOCK_REALTIME,&stop);
        total_time += ((stop.tv_sec-start.tv_sec)*1000000000) + (stop.tv_nsec - start.tv_nsec);
        for(vector<DATA_TYPE>::iterator it = output.begin(), e = output.end(); it != e; ++it){
          *it = set1[0];
	}
	break;
      default:
	assert(false);
      }
      noCopy = true;
    }

    set1.clear();
    set2.clear();
    output.clear();
  }

  printf("%lu\n", total_time);

  return 0;
}
