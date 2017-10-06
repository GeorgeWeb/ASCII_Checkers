#include "Board.hpp"

#include <iostream>
#include <algorithm>

namespace CheckerZ
{
	Board::Board() 
	{ }

	Board::~Board()
	{ }

	void Board::populate()
	{
		unsigned short count = 0;
		std::for_each(m_board.begin(), m_board.end(), [&](TABLE::grid<s_boardY> &grid)
		{ 
			std::for_each(grid.begin(), grid.end(), [&](TABLE::square &square)
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

	void Board::display()
	{
		std::cout << "\n\n\n\n";
		unsigned short count = 1;
		std::for_each(m_board.begin(), m_board.end(), [&](TABLE::grid<s_boardY> &grid)
		{
			std::cout << "\t\t\t\t\t\t";
			std::for_each(grid.begin(), grid.end(), [&](TABLE::square &square)
			{
				std::cout << square << " ";
				if (count++ % 8 == 0) std::cout << std::endl;
			});
		});
	}
}
