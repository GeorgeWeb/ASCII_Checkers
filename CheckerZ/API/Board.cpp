// project includes
#include "Board.hpp"

// std::includes
#include <iostream>
#include <algorithm>

namespace CheckerZ { namespace API {
	
	Board::Board()
	{ }

	Board::~Board()
	{ }

	void Board::populate()
	{
		uint16 count{ 0 };
		std::for_each(m_board.begin(), m_board.end(), [&](grid<s_boardY>& grid)
		{
			std::for_each(grid.begin(), grid.end(), [&](square& square)
			{
				if (count < 24) // PLAYER 1
				{
					if (count < 8)
						square = (count % 2) ? 'B' : '.';
					else if (count >= 8 && count < 16)
						square = !(count % 2) ? 'B' : '.';
					else if (count >= 16 && count < 24)
						square = (count % 2) ? 'B' : '.';
				}
				else if (count >= 40) // PLAYER 2
				{
					if (count < 48)
						square = !(count % 2) ? 'R' : '.';
					else if (count >= 48 && count < 56)
						square = (count % 2) ? 'R' : '.';
					else if (count >= 56 && count < 64)
						square = !(count % 2) ? 'R' : '.';
				}
				else
					square = '.';

				count++;
			});
		});
	}

	void Board::display() const
	{
		std::cout << "\n\n\n\n";
		uint16 count{ 1 };
		std::for_each(m_board.cbegin(), m_board.cend(), [&](const grid<s_boardY>& grid)
		{
			std::cout << "\t\t\t\t\t\t";
			std::for_each(grid.cbegin(), grid.cend(), [&](const square square)
			{
				std::cout << square << " ";
				if (count++ % 8 == 0) std::cout << std::endl;
			});
		});
	}

} }