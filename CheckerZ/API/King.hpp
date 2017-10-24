#ifndef KING_HPP
#define KING_HPP

// project includes
#include "Pawn.hpp"

namespace CheckerZ { namespace API {

	class King : public Pawn
	{
		public:
			const std::string getType() const override final { return std::string("King"); }
	};
} }
#endif !KING_HPP