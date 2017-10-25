#ifndef BOARD_HPP
#define BOARD_HPP

// project includes
#include "Pawn.hpp"

// std::includes
#include <array>
#include <algorithm>

namespace CheckerZ { namespace API {

	class Board final
	{
		template<class Type, const size_t Size>
		using board = std::array<std::array<Type, Size>, Size>;

		private:
			// TODO: boardX and boardY should become boardSize since it is always going to be a SQUARE!
			static constexpr uint16 s_boardLen = 8;
			// initialize board
			board<Pawn, s_boardLen> m_board;

			std::vector<Pawn> m_emptySlots;
			std::vector<Pawn> m_blackPawns;
			std::vector<Pawn> m_redPawns;

		public:
			Board();
			~Board();

			inline board<Pawn, s_boardLen>& getBoard() { return m_board; }
			inline Pawn& getPawnFromInput(const vec2& t_pos) { return m_board[t_pos.first - 'A'][t_pos.second - 1]; }

			std::vector<Pawn>& getEmptySlots();
			std::vector<Pawn>& getPawnsByColor(const std::string& t_color);

			void swapBoardGrids(Pawn& t_lhs, Pawn& t_rhs);

			// This function will be called after every move
			void populate();
			// This function will be called after every move
			void display() const;
	};

} }

#endif // !BOARD_HPP
