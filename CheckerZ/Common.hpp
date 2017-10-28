#ifndef COMMON_HPP
#define COMMON_HPP

// std::includes
#include <utility>

namespace CheckerZ
{
	// 8, 16, 32, 64-bit singed integral types
	using int8   = signed char;
	using int16  = signed short;
	using int32  = signed int;
	using int64  = signed long long;
	// 8, 16, 32, 64-bit unsinged integral types
	using uint8  = unsigned char;
	using uint16 = unsigned short;
	using uint32 = unsigned int;
	using uint64 = unsigned long long;

	// helper data structs
	using Position = std::pair<size_t, size_t>;
	using Movement = std::pair<Position, Position>;
}

// project includes
#include "API/Utils/Logger.hpp"
// concurrent programming lib - C++AMP
#include "Parallelism/Parallel.hpp"

#endif !COMMON_HPP