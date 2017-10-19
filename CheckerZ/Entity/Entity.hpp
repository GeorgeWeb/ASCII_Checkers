#ifndef ENTITY_HPP
#define ENTITY_HPP

// project includes
#include "../API/Board.hpp"

// std::includes
#include <vector>

namespace CheckerZ { namespace Entity {

	class Entity
	{
		public:
			Entity() { m_pawns.reserve(12); }
			virtual ~Entity() = default;

			virtual void movePawn(const uint16 t_pawnIdx, const vec2 &t_pos) = 0;
			virtual void takePawn(const uint16 t_pawnIdx) = 0;
			
			virtual std::vector<API::square>& getPawns() { return m_pawns; };
			// TODO: Assert that index is less than 16 ...
			virtual const API::square getPawn(uint16 t_index) { return m_pawns[t_index]; };

			virtual const API::Board* getBoard() { return m_board; }
			virtual void setBoard(API::Board* t_board) { m_board = t_board; }

		protected:
			API::Board* m_board;
			std::vector<API::square> m_pawns;
	};

} }
#endif !ENTITY_HPP