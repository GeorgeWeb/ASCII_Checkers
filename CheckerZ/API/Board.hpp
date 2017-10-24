#ifndef BOARD_HPP
#define BOARD_HPP

// project includes
#include "Pawn.hpp"

// std::includes
#include <array>

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

			inline const board<Pawn, s_boardLen>& getBoard() const { return m_board; }
			inline Pawn& getPawnGrid(const vec2& t_pos) { return m_board[t_pos.first - 'A'][t_pos.second - 1]; }

			const std::vector<Pawn>& getEmptySlots();
			const std::vector<Pawn>& getPawnsByColor(const std::string& t_color);

			inline void swapBoardGrids(Pawn& t_lhs, Pawn& t_rhs) { std::swap(t_lhs.mesh, t_rhs.mesh); }

			// This will be called inside an entity
			void translate(const vec2& t_posFrom, const vec2& t_posTo);
			void erase(const vec2& t_posFrom, const vec2& t_posTo);
			// This function will be called after every move
			void populate();
			// This function will be called after every move
			void display() const;
	};

} }

#endif // !BOARD_HPP
