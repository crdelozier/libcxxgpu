#ifndef _GPU_UTIL_H
#define _GPU_UTIL_H 1

/*
 * Rough complexity levels of CPU algorithm being acclerated
 * e.g. std::find = 1, std::min_element = 2, std::sort = 3
 */

#define _CPU_1 1
#define _CPU_2 2
#define _CPU_3 3

#ifdef STL_ENABLE_GPU
#define STL_GPU_END }
#else
#define STL_GPU_END
#endif

#ifdef STL_ENABLE_GPU

 bool __should_use_gpu(int __complexity, unsigned long __size){
   return true;
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
