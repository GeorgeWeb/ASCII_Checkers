#include "Player.hpp"

namespace CheckerZ { namespace Entity { namespace Player {

	using namespace API;

	Player::Player(const std::string& t_color) : Entity()
	{
		auto pawnsFromBoard = m_board->getPawnsByColor(t_color);
		// copy pawn data generated from the board
		std::copy(pawnsFromBoard.begin(), pawnsFromBoard.end(), std::back_inserter(m_pawns));
	}

	void Player::movePawn(const uint16 t_pawnIdx, const vec2 &t_pos)
	{
		m_board->setPos(t_pos);
	}

	void Player::takePawn(const uint16 t_pawnIdx)
	{
		// e.g. / temp:
		//auto pawnMesh = getPawn(t_pawnIdx).mesh;
		//getPawns().erase(getPawns().begin() + pawnMesh);
	}

} } }