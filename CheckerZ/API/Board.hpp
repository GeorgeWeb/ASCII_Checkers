#ifndef BOARD_HPP
#define BOARD_HPP

// project includes
#include "../Common.hpp"

// std::includes
#include <array>

namespace CheckerZ { namespace API {

	#pragma region Checkers Table Properties
	// define a square of the grid
	using square = uint8;
	// define the grid of the board
	template<class Type, const uint16 Size>
	using grid = std::array<Type, Size>;
	// define a board matrix
	template<class Type, const uint16 SizeX, const uint16 SizeY>
	using board = std::array<grid<Type, SizeY>, SizeX>;
	#pragma endregion

	class Board final
	{
		private:
			// TODO: boardX and boardY should become boardSize since it is always going to be a SQUARE!
			static constexpr uint16 s_boardLen = 8;
			// initialize board
			board<square, s_boardLen, s_boardLen> m_board;

		public:
			Board();
			~Board();

			inline const board<square, s_boardLen, s_boardLen>& const getBoard() const { return m_board; }
			std::array<square, 12> getPawnsByColor(const std::string& t_color);

			// This will be called inside an entity
			void setPos(vec2 t_pos);
			// This function will be called after every move
			void populate();
			// This function will be called after every move
			void display() const;
	};

} }

#endif // !BOARD_HPP
