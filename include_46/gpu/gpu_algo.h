#ifndef _GPU_ALGO
#define _GPU_ALGO 1

  template<typename _InputIterator, typename _OutputIterator,
	   typename _UnaryOperation>
    _OutputIterator
    __gpu_transform(_InputIterator __first, _InputIterator __last,
	      _OutputIterator __result, _UnaryOperation __unary_op)
    {
      typedef typename std::iterator_traits<_InputIterator>::value_type
	_ValueType;

      unsigned long __size = __last - __first;

      thrust::device_vector<_ValueType> __device(__size);
      thrust::device_vector<_ValueType> __output(__size);

      __copy_to_gpu(__first,__last,__device,__size);
 
      thrust::transform(__device.begin(),__device.end(),__output.begin(),__unary_op);

      __copy_from_gpu(__result,__result+__size,__output,__size);

      return __result;
    }


  template<typename _RandomAccessIterator, typename _Tp>
    _RandomAccessIterator
    __gpu_find(_RandomAccessIterator __first, _RandomAccessIterator __last,
	   const _Tp& __val)
    {
      static bool __first_time = true;
      unsigned long __total_size = (__last - __first);

      thrust::device_vector<_Tp> __device(__total_size);
      
      if(__first_time){
	__copy_to_gpu(__first,__last,__device,__total_size);
	__first_time = false;
      }

      typename thrust::device_vector<_Tp>::iterator __loc = 
	thrust::find(__device.begin(),__device.end(),__val);

      unsigned long __dist = thrust::distance(__device.begin(),__loc);

      return __first + __dist;
    }

   template<typename _ForwardIterator>
    _ForwardIterator
    __gpu_min_element(_ForwardIterator __first, _ForwardIterator __last)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type 
	_ValueType;
      
      unsigned long __size = __last - __first;

      thrust::device_vector<_ValueType> __device(__size);

      __copy_to_gpu(__first,__last,__device,__size);

      typename thrust::device_vector<_ValueType>::iterator __loc = 
	thrust::min_element(__device.begin(),__device.end());

      unsigned long __dist = thrust::distance(__device.begin(),__loc);

      return __first + __dist;
    }

// TODO:  min_element with user-defined comparator

  template<typename _ForwardIterator>
    _ForwardIterator
    __gpu_max_element(_ForwardIterator __first, _ForwardIterator __last)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type 
	_ValueType;
      
      unsigned long __size = __last - __first;

      thrust::device_vector<_ValueType> __device(__size);

      __copy_to_gpu(__first,__last,__device,__size);

      typename thrust::device_vector<_ValueType>::iterator __loc = 
	thrust::max_element(__device.begin(),__device.end());

      unsigned long __dist = thrust::distance(__device.begin(),__loc);

      return __first + __dist;
    }

// TODO:  max_element with user-defined comparator

  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator>
    _OutputIterator
    __gpu_set_union(_InputIterator1 __first1, _InputIterator1 __last1,
	      _InputIterator2 __first2, _InputIterator2 __last2,
		    _OutputIterator __result, bool __no_copy = false)
    {
      typedef typename std::iterator_traits<_InputIterator1>::value_type
	_ValueType;

      unsigned long __size1 = __last1 - __first1;
      unsigned long __size2 = __last2 - __first2;
      unsigned long __out_size = __size1 + __size2;

      thrust::device_vector<_ValueType> __device1(__size1);
      thrust::device_vector<_ValueType> __device2(__size2);
      thrust::device_vector<_ValueType> __device_out(__out_size);

      if(!__no_copy){
	__copy_to_gpu(__first1,__last1,__device1,__size1);
	__copy_to_gpu(__first2,__last2,__device2,__size2);
      }

      thrust::set_union(__device1.begin(),__device1.end(),
			__device2.begin(),__device2.end(),
			__device_out.begin());

      __copy_from_gpu(__result,__result + __out_size,__device_out,__out_size);

      return __result;
    }

  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator>
    _OutputIterator
    __gpu_set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
	      _InputIterator2 __first2, _InputIterator2 __last2,
			   _OutputIterator __result, bool __no_copy = false)
    {
      typedef typename std::iterator_traits<_InputIterator1>::value_type
	_ValueType;

      unsigned long __size1 = __last1 - __first1;
      unsigned long __size2 = __last2 - __first2;
      unsigned long __out_size = (__size1 < __size2) ? __size1 : __size2;

      thrust::device_vector<_ValueType> __device1(__size1);
      thrust::device_vector<_ValueType> __device2(__size2);
      thrust::device_vector<_ValueType> __device_out(__out_size);

      if(!__no_copy){
	__copy_to_gpu(__first1,__last1,__device1,__size1);
	__copy_to_gpu(__first2,__last2,__device2,__size2);
      }

      thrust::set_intersection(__device1.begin(),__device1.end(),
			__device2.begin(),__device2.end(),
			__device_out.begin());

      __copy_from_gpu(__result,__result + __out_size,__device_out,__out_size);

      return __result;
    }

    template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator>
    _OutputIterator
    __gpu_set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
	      _InputIterator2 __first2, _InputIterator2 __last2,
			 _OutputIterator __result, bool __no_copy = false)
    {
      typedef typename std::iterator_traits<_InputIterator1>::value_type
	_ValueType;

      unsigned long __size1 = __last1 - __first1;
      unsigned long __size2 = __last2 - __first2;
      unsigned long __out_size = __size1;

      thrust::device_vector<_ValueType> __device1(__size1);
      thrust::device_vector<_ValueType> __device2(__size2);
      thrust::device_vector<_ValueType> __device_out(__out_size);

      if(!__no_copy){
	__copy_to_gpu(__first1,__last1,__device1,__size1);
	__copy_to_gpu(__first2,__last2,__device2,__size2);
      }

      thrust::set_difference(__device1.begin(),__device1.end(),
			__device2.begin(),__device2.end(),
			__device_out.begin());

      __copy_from_gpu(__result,__result + __out_size,__device_out,__out_size);

      return __result;
    }

  template<typename _InputIterator1, typename _InputIterator2,
	   typename _OutputIterator>
    _OutputIterator
    __gpu_set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
	      _InputIterator2 __first2, _InputIterator2 __last2,
				   _OutputIterator __result, bool __no_copy = false)
    {
      typedef typename std::iterator_traits<_InputIterator1>::value_type
	_ValueType;

      unsigned long __size1 = __last1 - __first1;
      unsigned long __size2 = __last2 - __first2;
      unsigned long __out_size = (__size1 > __size2) ? __size1 : __size2;

      thrust::device_vector<_ValueType> __device1(__size1);
      thrust::device_vector<_ValueType> __device2(__size2);
      thrust::device_vector<_ValueType> __device_out(__out_size);

      if(!__no_copy){
	__copy_to_gpu(__first1,__last1,__device1,__size1);
	__copy_to_gpu(__first2,__last2,__device2,__size2);
      }

      thrust::set_symmetric_difference(__device1.begin(),__device1.end(),
			__device2.begin(),__device2.end(),
			__device_out.begin());

      __copy_from_gpu(__result,__result + __out_size,__device_out,__out_size);

      return __result;
    }

  template<typename _RandomAccessIterator>
    inline void
    __gpu_sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename std::iterator_traits<_RandomAccessIterator>::value_type
	_ValueType;

      unsigned long __total_size = (__last - __first);
      
      thrust::device_vector<_ValueType> __device(__total_size);
      
      __copy_to_gpu(__first,__last,__device,__total_size);

      thrust::sort(__device.begin(),__device.end());

      __copy_from_gpu(__first,__last,__device,__total_size); 
    }

#endif
