#ifndef MOVE_GENERATOR_HPP
#define MOVE_GENERATOR_HPP

// project includes
#include "../Board.hpp"

// std::includes
#include <deque>

namespace CheckerZ { namespace API { namespace Utils {

	class MovesGenerator
	{
		private:
			std::deque<Movement> m_possibleMoves;

		public:
			MovesGenerator() = default;
			~MovesGenerator() = default;

			inline const std::deque<Movement>& getPossibleMoves() const { return m_possibleMoves; }
			void generatePossibleMoves(std::shared_ptr<Board> t_board, const std::string& t_color, std::shared_ptr<Pawn> t_lastPlayedPawn = nullptr);
			void reset(std::shared_ptr<Board> t_board, const std::string& t_color, std::shared_ptr<Pawn> t_lastPlayedPawn);
			inline void clear() { m_possibleMoves.clear(); }
		
		private:
			void checkLeftMove(Board& t_board, int x, int y, const std::string& t_pos);
			void checkRightMove(Board& t_board, int x, int y, const std::string& t_pos);
			void checkLeftJump(Board& t_board, int x, int y, const std::string& t_pos);
			void checkRightJump(Board& t_board, int x, int y, const std::string& t_pos);
	};

} } }
#endif // !MOVE_GENERATOR_HPP