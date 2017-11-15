#include "AI.hpp"
#include <limits>

namespace CheckerZ { namespace Entity { namespace AI {

	void HardAI::firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator)
	{
		AI::firePawnAction(t_moveGenerator);

		t_moveGenerator->generatePossibleMoves(m_board, m_pawnColor, m_lastPlayedPawn);
		auto possibleMoves = t_moveGenerator->getPossibleMoves();
		
		// break out if there's no more possible moves
		if (possibleMoves.empty())
			return;

		// minimax (maximin) algorithm (with alpha-beta cutoffs)

		auto maximinMove = maximin(*m_board, 0);
		Position fromPos = maximinMove.first;
		Position toPos = maximinMove.second;
		// do movement
		//move(fromPos, toPos);
		m_board->move(fromPos, toPos);
	}

	Movement HardAI::maximin(const API::Board& t_board, uint32 t_depth)
	{
		API::Utils::MovesGenerator moveGenerator;

		// get all valid/possible moves in from the generator
		moveGenerator.generatePossibleMoves(m_board, m_pawnColor, m_lastPlayedPawn);
		auto possibleMoves = moveGenerator.getPossibleMoves();

		// break out if there's no more possible moves
		if (possibleMoves.empty())
			return Movement{ {0, 0}, {0, 0} };

		std::array<int32, 32> scores;
		for (int i = 0; i < scores.size(); i++) scores[i] = 0;
		size_t count = 0;
		for (auto posMove : possibleMoves)
		{
			API::Board board;
			board.setBoard(t_board.getBoard());

			scores[count] = MIN(board, t_depth + 1, posMove);
			count++;
		}

		int32 maxVal = scores[0];
		size_t maxPos = 0;
		// go through scores and find POS of maxScore
		for (size_t i = 0; i < possibleMoves.size(); i++)
		{
			if (maxVal < scores[i])
			{
				maxVal = scores[i];
				maxPos = i;
			}
		}
		
		// get the best move based on the max score positon
		return possibleMoves[maxPos];
	}

	int32 HardAI::MIN(API::Board t_board, uint32 t_depth, Movement t_move)
	{
		t_board.move(t_move.first, t_move.second);

		API::Utils::MovesGenerator moveGenerator;

		auto color = (m_pawnColor == "Red") ? "Black" : "Red";
		// get all valid/possible moves in from the generator
		moveGenerator.generatePossibleMoves(m_board, color, m_lastPlayedPawn);

		auto possibleMoves = moveGenerator.getPossibleMoves();

		if (possibleMoves.empty())
		{
			return hasFoundEnemy(t_board, color) ? 1000 : -1000;
		}
		
		std::array<int32, 32> scores;
		for (int i = 0; i < scores.size(); i++) scores[i] = 0;
		size_t count = 0;
		for (auto posMove : possibleMoves)
		{
			scores[count] = MAX(t_board, t_depth + 1, posMove);
			count++;
		}

		std::stable_sort(scores.begin(), scores.end(), std::less<int32>());
		return scores[0];
	}

	int32 HardAI::MAX(API::Board t_board, uint32 t_depth, Movement t_move)
	{
		t_board.move(t_move.first, t_move.second);

		API::Utils::MovesGenerator moveGenerator;

		if (t_depth >= 2)
			return calculateBoard(t_board);

		// get all valid/possible moves in from the generator
		moveGenerator.generatePossibleMoves(m_board, m_pawnColor, m_lastPlayedPawn);
		auto possibleMoves = moveGenerator.getPossibleMoves();

		if (possibleMoves.empty())
			return hasFoundEnemy(t_board, m_pawnColor) ? 1000 : -1000;
		
		std::array<int32, 32> scores;
		for (int i = 0; i < scores.size(); i++) scores[i] = 0;
		size_t count = 0;
		for (auto posMove : possibleMoves)
		{
			scores[count] = MIN(t_board, t_depth + 1, posMove);
			count++;
		}

		std::stable_sort(scores.begin(), scores.end(), std::greater<int32>());
		return scores[0];
	}

	int32 HardAI::calculateBoard(API::Board t_board)
	{
		int32 score = 0;

		// color/side helpers
		auto myColor = m_pawnColor;
		auto enemyColor = (myColor == "Red") ? "Black" : "Red";
		auto emptyColor = "Empty";

		// evaluate the game board at its current state
		for (size_t row = 0; row < t_board.getBoard().size(); row++)
		{
			for (size_t col = 0; col < t_board.getBoard().size(); col++)
			{
				auto pawn = t_board.getBoardPawn(row, col);
				auto pawnMesh = pawn.getMesh();
				auto pawnColor = pawn.getColor();

				// TODO: implement these!!!!
				API::Pawn middlePawn;
				API::Pawn postJumpPawn;

				// own pawn +5
				if (pawnColor == myColor && islower(pawnMesh))
					score += 5;
				// enemy pawn -5
				else if (pawnColor == enemyColor && islower(pawnMesh))
					score -= 5;
				// own king +10
				else if (pawnColor == myColor && isupper(pawnMesh))
					score += 10;
				// enemy king -10
				else if (pawnColor == enemyColor && isupper(pawnMesh))
					score -= 10;
				// enemy pawn I can take +13
				else if (pawnColor == myColor && middlePawn.getColor() == enemyColor && islower(middlePawn.getMesh()) && postJumpPawn.getColor() == emptyColor)
					score += 13;
				// own pawn can be taken by enemy -15
				else if (pawnColor == enemyColor && middlePawn.getColor() == myColor && islower(middlePawn.getMesh()) && postJumpPawn.getColor() == emptyColor)
					score -= 15;
				// enemy king I can take +22
				else if (pawnColor == myColor && middlePawn.getColor() == enemyColor && isupper(middlePawn.getMesh()) && postJumpPawn.getColor() == emptyColor)
					score += 13;
				// own king can be taken by enemy -26
				else if (pawnColor == enemyColor && middlePawn.getColor() == myColor && isupper(middlePawn.getMesh()) && postJumpPawn.getColor() == emptyColor)
					score -= 15;

				// own pawn close to wall +7
				// enemy pawn close to wall -8
			}
		}

		return score;
	}

	bool HardAI::hasFoundEnemy(API::Board t_board, const std::string& t_color) const
	{
		for (size_t row = 0; row < t_board.getBoard().size(); row++)
			for (size_t col = 0; col < t_board.getBoard().size(); col++)
				if (t_board.getBoardPawn(row, col).getColor() != t_color && t_board.getBoardPawn(row, col).getColor() != "Empty")
					return true;

		return false;
	}

} } }