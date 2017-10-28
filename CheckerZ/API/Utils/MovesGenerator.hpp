#ifndef MOVE_GENERATOR_HPP
#define MOVE_GENERATOR_HPP

// std::includes
#include <deque>
#include "../Board.hpp"

namespace CheckerZ { namespace API { namespace Utils {

	class MovesGenerator
	{
		private:
			std::deque<Movement> m_possibleMoves;
		
		public:
			MovesGenerator() = default;
			~MovesGenerator() = default;

			inline const std::deque<Movement>& getPossibleMoves() { return m_possibleMoves; }
			void generatePossibleMoves(std::shared_ptr<Board> t_board, const std::string& t_color, Pawn* replayablePawn);
	};

} } }
#endif // !MOVE_GENERATOR_HPP
