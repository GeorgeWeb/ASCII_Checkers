#ifndef BOARD_HPP
#define BOARD_HPP

// project includes
#include "Pawn.hpp"

// std::includes
#include <array>
#include <algorithm>

namespace CheckerZ { namespace API {

	enum GridInfo
	{
		BLACK,
		RED,
		EMPTY,
		EOB
	};

	class Board final
	{
		template<class Type, const size_t Size>
		using board = std::array<std::array<Type, Size>, Size>;

		private:
			// TODO: boardX and boardY should become boardSize since it is always going to be a SQUARE!
			static constexpr uint16 s_boardLen = 8;
			// initialize board
			board<Pawn, s_boardLen> m_board;

		public:
			Board() = default;
			~Board() = default;

			inline const board<Pawn, s_boardLen>& getBoard() const { return m_board; }
			
			// easy fast getter
			inline Pawn& getBoardPawn(size_t t_row, size_t t_col) { return m_board[t_row][t_col]; }

			GridInfo getGridInfo(int t_row, int t_col);

			// This function will be called after every move
			void populate();
			// This function will be called after every move
			void display() const;
			// ...
			void move(const Position& t_posFrom, Position&& t_posTo);
			// ...
			void evolve(Pawn& t_pawn);

		private:
			void swapPawns(Pawn& t_lhs, Pawn& t_rhs);
			void killPawn(Pawn& t_pawn);
	};

} }

#endif // !BOARD_HPP
