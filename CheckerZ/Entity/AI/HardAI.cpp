#include "AI.hpp"

#define MAX_LEVEL 2

namespace CheckerZ { namespace Entity { namespace AI {

	void HardAI::firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator)
	{
		AI::firePawnAction(t_moveGenerator);

		t_moveGenerator->generatePossibleMoves(m_board, m_pawnColor, m_lastPlayedPawn);
		auto possibleMoves = t_moveGenerator->getPossibleMoves();
		
		// break out if there's no more possible moves
		if (possibleMoves.empty())
			return;

		// minimax (maximin) algorithm

		auto maximinMove = maximin(*m_board, 0);
		Position fromPos = maximinMove.first;
		Position toPos = maximinMove.second;
		// do movement
		move(fromPos, toPos);
	}

	Movement HardAI::maximin(API::Board t_board, uint32 t_depth)
	{
		API::Utils::MovesGenerator moveGenerator;

		// get all valid/possible moves in from the generator
		auto p_board = std::make_shared<API::Board>(); *p_board = t_board;
		moveGenerator.generatePossibleMoves(p_board, m_pawnColor, m_lastPlayedPawn);
		auto possibleMoves = moveGenerator.getPossibleMoves();

		// break out if there's no more possible moves
		if (possibleMoves.empty())
			return Movement{ {0, 0}, {0, 0} };
		
		// populate with scores for every possible move
		std::array<int32, 32> scores;
		for (int i = 0; i < scores.size(); i++) scores[i] = 0;
		size_t count = 0;
		for (auto posMove : possibleMoves)
		{
			scores[count] = MIN(t_board, t_depth + 1, posMove);
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
		// apply test move on the temp board
		t_board.move(t_move.first, t_move.second);

		API::Utils::MovesGenerator moveGenerator;

		auto color = (m_pawnColor == "Red") ? "Black" : "Red";
		// get all valid/possible moves in from the generator
		auto p_board = std::make_shared<API::Board>(); *p_board = t_board;
		moveGenerator.generatePossibleMoves(p_board, color, m_lastPlayedPawn);

		auto possibleMoves = moveGenerator.getPossibleMoves();

		// if no possible moves return an enormously big score
		if (possibleMoves.empty())
			return hasFoundEnemy(t_board, color) ? 10000 : -10000;
		
		// populate with scores for every possible move
		std::array<int32, 32> scores;
		for (int32 i = 0; i < scores.size(); i++) scores[i] = 0;
		size_t count = 0;
		for (auto posMove : possibleMoves)
		{
			scores[count] = MAX(t_board, t_depth + 1, posMove);
			count++;
		}

		std::sort(scores.begin(), scores.end(), std::less<int32>());
		return scores[0];
	}

	int32 HardAI::MAX(API::Board t_board, uint32 t_depth, Movement t_move)
	{
		// apply test move on the temp board
		t_board.move(t_move.first, t_move.second);

		API::Utils::MovesGenerator moveGenerator;

		// exit recursion
		if (t_depth >= MAX_LEVEL)
			return calculateBoard(t_board);

		// get all valid/possible moves in from the generator
		auto p_board = std::make_shared<API::Board>(); *p_board = t_board;
		moveGenerator.generatePossibleMoves(p_board, m_pawnColor, m_lastPlayedPawn);
		auto possibleMoves = moveGenerator.getPossibleMoves();

		// if no possible moves return an enormously big score
		if (possibleMoves.empty())
			return hasFoundEnemy(t_board, m_pawnColor) ? 10000 : -10000;
		
		// populate with scores for every possible move
		std::array<int32, 32> scores;
		for (int32 i = 0; i < scores.size(); i++) scores[i] = 0;
		size_t count = 0;
		for (auto posMove : possibleMoves)
		{
			scores[count] = MIN(t_board, t_depth + 1, posMove);
			count++;
		}

		std::sort(scores.begin(), scores.end(), std::greater<int32>());
		return scores[0];
	}

	int32 HardAI::calculateBoard(API::Board t_board)
	{
		int32 score = 0;

		auto myColor = m_pawnColor;
		auto enemyColor = (myColor == "Red") ? "Black" : "Red";
		auto emptyColor = "Empty";

		API::Utils::MovesGenerator moveGenerator;
		auto p_board = std::make_shared<API::Board>(); *p_board = t_board;

		// evaluate the game board at its current state
		for (size_t row = 0; row < t_board.getBoard().size(); row++)
		{
			for (size_t col = 0; col < t_board.getBoard().size(); col++)
			{
				auto pawn = t_board.getBoardPawn(row, col);
				auto pawnMesh = pawn.getMesh();
				auto pawnColor = pawn.getColor();

				// own pawn - DON'T CARE
				/*
				if (pawnColor == myColor && !pawn.isKing())
					score += 0;
				*/

				// enemy pawn
				if (pawnColor == enemyColor && !pawn.isKing())
					score -= 10;
				
				// own king - DON'T CARE
				/*
				if (pawnColor == myColor && pawn.isKing())
					score += 0;
				*/

				// enemy king
				if (pawnColor == enemyColor && pawn.isKing())
					score -= 20;

				// own pawn close to wall - DON'T CARE
				/*
				if (pawnColor == myColor && !pawn.isKing() && (pawn.getCoordX() == t_board.s_boardLen - 1 || pawn.getCoordX() == 0))
				score += 0;
				*/

				// enemy pawn close to wall
				if (pawnColor == enemyColor && !pawn.isKing() && (pawn.getCoordX() == t_board.s_boardLen - 1 || pawn.getCoordX() == 0))
					score -= 7;
			}
		}

		// get all valid/possible moves in from the generator for my self
		moveGenerator.generatePossibleMoves(p_board, m_pawnColor, m_lastPlayedPawn);
		auto myPossibleMoves = moveGenerator.getPossibleMoves();

		if (myPossibleMoves.empty())
			return hasFoundEnemy(t_board, myColor) ? 10000 : -10000;

		// possible actions I can do
		for (auto move : myPossibleMoves)
		{
			auto action = std::abs(static_cast<int>(move.first.first - move.second.first) + std::abs(static_cast<int>(move.first.second - move.second.second)));
			auto isJump = action == 4;

			auto startPawn = t_board.getBoardPawn(move.first);
			auto endPawn = t_board.getBoardPawn(move.second);
			auto midPawn = t_board.getBoard()[(t_board.getBoardPawn(move.first).getCoordX() + t_board.getBoardPawn(move.second).getCoordX()) / 2]
										     [(t_board.getBoardPawn(move.first).getCoordY() + t_board.getBoardPawn(move.second).getCoordY()) / 2];

			// Helper evaluation data:
			auto startColor = startPawn.getColor();
			auto endColor = endPawn.getColor();
			auto midColor = midPawn.getColor();

			if (isJump)
			{
				// enemy pawn I can take
				if (startColor == myColor && midColor == enemyColor && !midPawn.isKing() && endColor == emptyColor)
					score += 30;

				// enemy king I can take
				if (startColor == myColor && midColor == enemyColor && midPawn.isKing() && endColor == emptyColor)
					score += 50;
			}
		}
		
		// get all valid/possible moves in from the generator for the enemy
		moveGenerator.generatePossibleMoves(p_board, enemyColor, m_lastPlayedPawn);
		auto enemyPossibleMoves = moveGenerator.getPossibleMoves();

		if (enemyPossibleMoves.empty())
			return hasFoundEnemy(t_board, enemyColor) ? 1000 : -1000;

		// possible actions enemy can do
		for (auto move : enemyPossibleMoves)
		{
			auto action = std::abs(static_cast<int>(move.first.first - move.second.first) + std::abs(static_cast<int>(move.first.second - move.second.second)));
			auto isJump = action == 4;

			auto startPawn = t_board.getBoardPawn(move.first);
			auto endPawn = t_board.getBoardPawn(move.second);
			auto midPawn = t_board.getBoard()[(t_board.getBoardPawn(move.first).getCoordX() + t_board.getBoardPawn(move.second).getCoordX()) / 2]
									     	 [(t_board.getBoardPawn(move.first).getCoordY() + t_board.getBoardPawn(move.second).getCoordY()) / 2];

			// Helper evaluation data:
			auto startColor = startPawn.getColor();
			auto endColor = endPawn.getColor();
			auto midColor = midPawn.getColor();
			
			if (isJump)
			{
				// own pawn can be taken by enemy
				if (startColor == enemyColor && midColor == myColor && !midPawn.isKing() && endColor == emptyColor)
					score -= 30;

				// own king can be taken by enemy
				if (startColor == enemyColor && midColor == myColor && midPawn.isKing() && endColor == emptyColor)
					score -= 50;
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