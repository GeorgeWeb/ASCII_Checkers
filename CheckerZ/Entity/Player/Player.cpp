#include "Player.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	bool Player::firePawnAction(const vec2& t_posFrom, vec2&& t_posTo)
	{	
		// check from board if you only need to translate or translate + erase:
		// get the entity's own picked pawn
		auto& myPawn = m_board->getPawnFromInput(t_posFrom);
		// get the other pawn picked for action by the entity
		auto& other = m_board->getPawnFromInput(t_posTo);
		
		bool isMovePossible = false;

		// check if it's this player's turn
		if (myPawn.getColor() == m_pawns[0].getColor())
		{
			for (size_t row = 0; row < m_board->getBoard().size() - 1; row++)
			{
				for (size_t col = 0; col < m_board->getBoard().size() - 1; col++)
				{
					// check for possible movement
					if (myPawn.getMesh() == m_board->getBoard()[row][col].getMesh() && myPawn.getMesh() != other.getMesh())
					{
						// check movement for pawn
						if (myPawn.getType() == "Pawn")
						{
							// check if player's top
							if (myPawn.getColor() == "Black")
							{
								if ((row > 0 && col < m_board->getBoard().size())
									&& other.getMesh() == m_board->getBoard()[row - 1][col + 1].getMesh()
									|| (row < m_board->getBoard().size() && col < m_board->getBoard().size())
									&& other.getMesh() == m_board->getBoard()[row + 1][col + 1].getMesh())
								{
									isMovePossible = true;
									break;
								}
							}
							// check if player's bottom
							else if (myPawn.getColor() == "Red")
							{
								if ((row > 0 && col > 0) 
									&& other.getMesh() == m_board->getBoard()[row - 1][col - 1].getMesh()
									|| (row < m_board->getBoard().size() && col > 0) 
									&& other.getMesh() == m_board->getBoard()[row + 1][col - 1].getMesh())
								{
									isMovePossible = true;
									break;
								}
							}
						}
						// check movement for king
						else if (myPawn.getType() == "King")
						{
							// TODO: Do checks for King specialization of Pawn
						}
						else { /* TODO */  }
					}
					else { /* TODO */ }
				}
			}
			
			// Movement options
			if (isMovePossible)
			{
				if (other.getMesh() != '.')
				{
					// remove the other pawn
					// TODO: Remove from the vector, etc.
					other.setValues('.', "White");
				}	
				// swap positions
				m_board->swapBoardGrids(myPawn, other);
			}

			return isMovePossible;
		}
	}

} } }