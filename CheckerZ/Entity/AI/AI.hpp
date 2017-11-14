#ifndef AI_HPP
#define AI_HPP

#include "../Entity.hpp"
#include "../../API/Events/EventManager.hpp"

// std::includes
#include <cassert>
#include <random>
#include <algorithm>

namespace CheckerZ { namespace Entity { namespace AI {

	// Base class for future types of AI
	class AI : public Entity
	{
		public: 
			AI() : Entity() { }
			virtual ~AI() = default;

			std::string getClassType() override { return std::string("AI"); }

			virtual void firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator) override
			{
				assert(std::is_sorted(t_moveGenerator->getPossibleMoves().begin(), t_moveGenerator->getPossibleMoves().end()));
			}
		
		protected:
			void randomMove(std::deque<Movement>& t_possibleMoves)
			{
				std::random_device rd;
				std::mt19937 engine(rd());
				std::uniform_int_distribution<size_t> dist(0, t_possibleMoves.size() - 1);
				size_t randIdx = dist(engine);
				Movement randMove = t_possibleMoves[randIdx];
				Position fromPos = randMove.first;
				Position toPos = randMove.second;
				// do movement
				move(fromPos, toPos);
			}

			void move(Position& t_fromPos, Position& t_toPos)
			{
				API::ActionState turnState = m_board->move(t_fromPos, t_toPos);

				// if an action has happened -> a pawn with coords: t_posFrom and a pawn with coords: t_posTo will have their values swapped
				if (turnState == API::ActionState::JUMP)
					m_lastPlayedPawn = std::make_shared<API::Pawn>(m_board->getBoardPawn(t_toPos));

				if (turnState == API::ActionState::MOVE)
					m_lastPlayedPawn = nullptr;
			}
	};
	
	// This AI type will simply pick a random possible move
	class EasyAI final : public AI
	{
		public:
			EasyAI() : AI() { setName("EasyAI"); }
			~EasyAI() = default;

			void firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator) override;
	};

	// This AI type class implements a custom greedy action picking algorithm
	class MediumAI final : public AI
	{
		public:
			MediumAI() : AI() { setName("MediumAI"); }
			~MediumAI() = default;

			void firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator) override;
	};

	// This AI type class implements the MinMax algorithm with AB-Pruning optimization
	class HardAI final : public AI
	{		
		public:
			HardAI() : AI() { setName("HardAI"); }
			~HardAI() = default;

			void firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator) override;

		private:
			void scoredMove(Position& t_fromPos, Position& t_toPos, int32 t_score);
			
			// min-max getters
			inline int32 getMin(const int32 t_first, const int32 t_second) { return t_first < t_second ? t_first : t_second; }
			inline int32 getMax(const int32 t_first, const int32 t_second) { return t_first > t_second ? t_first : t_second; }

			Movement* minimax(std::deque<Movement> t_validMovesList, uint32 t_depth, bool t_isMax);
	};

} } }
#endif !AI_HPP