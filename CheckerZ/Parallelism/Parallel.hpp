#ifndef PARALLEL_HPP
#define PARALLEL_HPP

// C++AMP include
#include <amp.h>

/**
 * Using C++AMP (C++ Accelerated Massive Parallelism): 
 * accelerates the execution of the C++ code by taking advantage of the data-parallel hardware 
 * that's commonly present as a graphics processing unit (GPU) on a discrete graphics card.
**/

namespace CheckerZ { namespace Parallelism {
		template<class Type, const size_t Size>
		using parallel_arr = concurrency::array_view<Type, Size>;
} }

#endif !PARALLEL_HPP