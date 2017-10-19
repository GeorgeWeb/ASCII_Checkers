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
			Entity(const std::string& t_name) : m_name(t_name) { m_pawns.reserve(12); }
			virtual ~Entity() = default;

			virtual void firePawnAction(const vec2& t_posFrom, const vec2 &t_posTo) = 0;

			virtual const std::string& getName() { return m_name; }
			// assign the game board to the entity
			virtual void setBoard(API::Board* t_board) { m_board = t_board; }
			// regulate turn states
			virtual bool hasTurn() { return m_hasTurn; }
			virtual void setTurn(bool t_hasTurn) { m_hasTurn = t_hasTurn; }
			// assign pawns to the entity from the game board
			void assignPawns(const std::string& t_color)
			{
				auto pawnsFromBoard = m_board->getPawnsByColor(t_color);;
				// copy pawn data generated from the board
				std::copy(pawnsFromBoard.begin(), pawnsFromBoard.end(), std::back_inserter(m_pawns));
			}

		protected:
			std::string m_name;
			API::Board* m_board;
			std::vector<API::square> m_pawns;
			bool m_hasTurn = false;
		
		protected: ///> force creation with name parameter
			Entity() = delete;
	};

} }
#endif !ENTITY_HPP