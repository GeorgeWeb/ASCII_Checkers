#ifndef COMMON_HPP
#define COMMON_HPP

namespace CheckerZ
{
	// 32-bit unsigned integral typedef
	using int32 = int;
	using uint32 = size_t; // std::unsigned int (typedef unsigned int size_t)
	using ushort32 = unsigned short;
	
	// 8-bit unsigned character typedef
	using uchar = unsigned char;
}

// project includes (concurrent programming lib - C++AMP)
#include "Parallelism/Parallel.hpp"

#endif !COMMON_HPP