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
			std::shared_ptr<API::Pawn> m_lastPlayedPawn = nullptr;
			// entity's turn state
			bool m_hasTurn = false;
		
		public:
			Entity() = default;
			virtual ~Entity() = default;

			void setName(const std::string& t_name) { m_name = t_name; }
			void setColor(const std::string& t_pawnColor) { m_pawnColor = t_pawnColor; }

			// does the player action - move or take
			// used for AI Entity
			virtual void firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator) {};
			// used for Human/Player Entity
			virtual void firePawnAction(const Position& t_posFrom, const Position& t_posTo, std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator) {};
			// determine the type of Entity - AI/CPU or Human/Player
			virtual std::string getClassType() = 0;

			inline std::shared_ptr<API::Pawn>& getLastPlayedPawn() { return m_lastPlayedPawn; }

			// turn regulation accessors (get/set)
			inline bool hasTurn() { return m_hasTurn; }
			inline void setTurn(bool t_hasTurn) { m_hasTurn = t_hasTurn; }

			// description accessors (getters-only)
			inline const std::string& getName() { return m_name; }
			inline const std::string& getPawnColor() { return m_pawnColor; }
			
			// assign the game board to the entity object
			inline void setBoard(std::shared_ptr<API::Board> t_board) { m_board = t_board; }
	};

} }
#endif !ENTITY_HPP