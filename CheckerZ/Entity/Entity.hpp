#ifndef ENTITY_HPP
#define ENTITY_HPP

// project includes
#include "../API/Board.hpp"

// std::includes
#include <vector>

namespace CheckerZ { namespace Entity {

	class Entity
	{
		protected:
			std::string m_name;
			std::shared_ptr<API::Board> m_board;
			std::vector<API::Pawn> m_pawns;
			bool m_hasTurn = false;

		public:
			Entity(const std::string& t_name) : m_name(t_name) { m_pawns.reserve(12); }
			virtual ~Entity() = default;

			// the only overridable func from player and AI
			virtual void firePawnAction(const vec2& t_posFrom, const vec2 &t_posTo) = 0;

		public:
			inline const std::string& getName() { return m_name; }
			// assign the game board to the entity
			inline void setBoard(std::shared_ptr<API::Board> t_board) { m_board = t_board; }
			// regulate turn states
			inline bool hasTurn() { return m_hasTurn; }
			inline void setTurn(bool t_hasTurn) { m_hasTurn = t_hasTurn; }
			// assign pawns to the entity from the game board
			void assignPawns(const std::string& t_color)
			{
				auto pawnsFromBoard = m_board->getPawnsByColor(t_color);;
				// copy pawn data generated from the board
				std::copy(pawnsFromBoard.begin(), pawnsFromBoard.end(), std::back_inserter(m_pawns));
			}		
			
		private: ///> force creation with name parameter
			Entity() = delete;
	};

} }
#endif !ENTITY_HPP