#ifndef BOARD_HPP
#define BOARD_HPP

// project includes
#include "../Common.hpp"

// std::includes
#include <array>

namespace CheckerZ { namespace API {

	#pragma region Checkers Table Properties
	// define a single board square
	using square = uint8;
	// define the board - matrix of squares
	template<class Type, const uint16 Size>
	using board = std::array<std::array<Type, Size>, Size>;
	#pragma endregion

	class Board final
	{
		private:
			// TODO: boardX and boardY should become boardSize since it is always going to be a SQUARE!
			static constexpr uint16 s_boardLen = 8;
			// initialize board
			board<square, s_boardLen> m_board;

			std::vector<square> m_emptySlots;
			std::vector<square> m_blackPawns;
			std::vector<square> m_redPawns;

		public:
			Board();
			~Board();

			inline const board<square, s_boardLen>& const getBoard() const { return m_board; }
			const std::vector<square>& getEmptySlots();
			const std::vector<square>& getPawnsByColor(const std::string& t_color);

			// This will be called inside an entity
			void translate(const vec2& t_posFrom, const vec2 &t_posTo);
			void erase(const vec2& t_posFrom, const vec2 &t_posTo);
			// This function will be called after every move
			void populate();
			// This function will be called after every move
			void display() const;
	};

} }

#endif // !BOARD_HPP
