#ifndef _GPU_UTIL_H
#define _GPU_UTIL_H 1

#ifdef GT9600
#define STL_GPU_BANDWIDTH 58
#define STL_GPU_CORE_COUNT 64
#define STL_GPU_CLOCK 1625
#endif

#ifdef GTX570
#define STL_GPU_BANDWIDTH 152
#define STL_GPU_CORE_COUNT 480
#define STL_GPU_CLOCK 1464
#endif

#ifndef STL_GPU_BANDWIDTH
#define STL_GPU_BANDWIDTH 152
#endif

#ifndef STL_GPU_CORE_COUNT
#define STL_GPU_CORE_COUNT 480
#endif

#ifndef STL_GPU_CLOCK
#define STL_GPU_CLOCK 1464
#endif

#define DEFAULT_BANDWIDTH_FACTOR 16
#define DEFAULT_BANDWIDTH 152
#define DEFAULT_CORE_COUNT 480
#define DEFAULT_CLOCK 1464

#define CALC_BANDWIDTH ((float)DEFAULT_BANDWIDTH) / ((float)STL_GPU_BANDWIDTH)
#define CALC_CORE_COUNT ((float)DEFAULT_CORE_COUNT) / ((float)STL_GPU_CORE_COUNT)
#define CALC_CLOCK ((float)DEFAULT_CLOCK) / ((float)STL_GPU_CLOCK)

#define CALC_TOTAL ((CALC_BANDWIDTH) * (CALC_CORE_COUNT) * (CALC_CLOCK))

#define GPU_FACTOR ((float)DEFAULT_BANDWIDTH_FACTOR) * CALC_TOTAL

#define STL_GPU_MIN_INSTRUCTION_CUTOFF 16

#define STL_GPU_TOTAL_INSTRUCTION_CUTOFF 3000000

/*
 * Macro lets us remove the ifdef and endif from each function end
 */

#ifdef STL_ENABLE_GPU
#define STL_GPU_END }
#else
#define STL_GPU_END
#endif

#ifdef STL_ENABLE_GPU

/*
 * Uses runtime heuristics to determine whether to use the GPU or not
 *
 * Heuristics used are based on the
 *   1) Approximate number of instructions per element (affects CPU more than GPU)
 *   2) Total number of elements that will be executed on (affects GPU more than CPU)
 *   3) Size of the elements (data type size)
 */

 inline bool __should_use_gpu(int,long,long __elem_size = 4)
   __attribute__((always_inline));

 inline bool __should_use_gpu(int __approx_instructions, long __size, long __elem_size)
 {
   // printf("%d, %ld, %ld, %1.4f\n",__approx_instructions,__size,__elem_size,GPU_FACTOR);

   // First heuristic just cuts off for small instruction sizes due to 
   // kernel launch and data transfer times dominating at this size
   if(__approx_instructions < STL_GPU_MIN_INSTRUCTION_CUTOFF){
     //printf("Cutoff1\n");
     return false;
   }

   long __instruction_factor = __size * __approx_instructions;

   // Second heuristic checks to see if total work size is too small, which 
   // also often indicates that the CPU should be used due to kernel startup costs
   if(__instruction_factor < STL_GPU_TOTAL_INSTRUCTION_CUTOFF){
     //printf("Cutoff2\n");
     return false;
   }

   // Final heuristic compares the work needed to transfer data versus the work needed to compute

   long __transfer_factor = (long)(((float)__size) * ((float)__elem_size) * (GPU_FACTOR * (32000.0 / (float)__size)));
   
   /*
   if(__transfer_factor - __instruction_factor < 0){
     printf("Using GPU %ld - %ld\n",__transfer_factor,__instruction_factor);
   }else{
     printf("Not using GPU %ld - %ld\n",__transfer_factor,__instruction_factor);
     }
   */
   
   return (__transfer_factor - __instruction_factor) < 0;
 }

/*
 * Copy data to GPU from an iterator
 * Attempts to optimize the copy in the case of contiguous memory layout
 */

  template<typename _Iterator, typename _Tp>
  void __copy_to_gpu(_Iterator __first, _Iterator __last, thrust::device_vector<_Tp> & __device, size_t __total_size){
    _Tp * __start = &(*__first);
    _Tp * __end = &(*(__last-1)) + 1;

    if(((char*)__end) - ((char*)__start) == __total_size * (sizeof(_Tp))){
      // Memory is continuous, so we can do a direct copy
      thrust::copy(__start,__end,__device.begin());
    }else{
      // Not provably continuous memory, so use iterators to copy
      thrust::host_vector<_Tp> __host(__total_size);
      unsigned long __idx = 0;
      for(; __first != __last; ++__first){
	__host[__idx] = *__first;
	++__idx;
      }
      thrust::copy(__host.begin(),__host.end(),__device.begin());
    }
  }

/*
 * Copy data from GPU to an iterator
 * Attempts to optimize the copy in the case of contiguous memory layout
 */

  template<typename _Iterator, typename _Tp>
  void __copy_from_gpu(_Iterator __first, _Iterator __last, thrust::device_vector<_Tp> & __device, size_t __total_size){
    _Tp * __start = &(*__first);
    _Tp * __end = &(*(__last-1)) + 1;

    if(((char*)__end) - ((char*)__start) == __total_size * (sizeof(_Tp))){
      // Memory is continuous, so we can do a direct copy
       thrust::copy(__device.begin(),__device.end(),__start);
    }else{
      // Not provably continuous memory, so use iterators to copy
      thrust::host_vector<_Tp> __host(__total_size);
      thrust::copy(__device.begin(),__device.end(),__host.begin());
      unsigned long __idx = 0;
      for(; __first != __last; ++__first){
	*__first = __host[__idx];
        ++__idx;
      }
    }
  }

#endif // STL_ENABLE_GPU
#endif // _GPU_UTIL
