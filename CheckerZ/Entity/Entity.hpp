#ifndef ENTITY_HPP
#define ENTITY_HPP

// project includes
#include "../API/Utils/MovesGenerator.hpp"

namespace CheckerZ { namespace Entity {

	class Entity
	{
		protected:
			// entity descriptive features
			std::string m_name;
			std::string m_pawnColor;
			// pointer to the game board -> used for movement checks
			std::shared_ptr<API::Board> m_board;
			// entity's turn state
			bool m_hasTurn = false;
		
		public:
			// Must be the only usable constructor !!!
			Entity(const std::string& t_name, const std::string& t_pawnColor) : 
				m_name(t_name), 
				m_pawnColor(t_pawnColor) { }
			virtual ~Entity() = default;

			// does the player action - move or take
			virtual void firePawnAction(const Position& t_posFrom, Position&& t_posTo, std::shared_ptr<API::Utils::MovesGenerator> moveGenerator) = 0;
			
			// turn regulation accessors (get/set)
			inline bool hasTurn() { return m_hasTurn; }
			inline void setTurn(bool t_hasTurn) { m_hasTurn = t_hasTurn; }

			// description accessors (getters-only)
			inline const std::string& getName() { return m_name; }
			inline const std::string& getPawnColor() { return m_pawnColor; }
			
			// assign the game board to the entity object
			inline void setBoard(std::shared_ptr<API::Board> t_board) { m_board = t_board; }
			
		private:
			// force Entity instantiatoin with its description parameters
			Entity() = delete;
	};

} }
#endif !ENTITY_HPP