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
			void performRandomMove(std::deque<Movement>& t_possibleMoves)
			{
				std::random_device rd;
				std::mt19937 engine(rd());
				std::uniform_int_distribution<size_t> dist(0, t_possibleMoves.size() - 1);
				size_t randIdx = dist(engine);
				Movement randMove = t_possibleMoves[randIdx];
				Position fromPos = randMove.first;
				Position toPos = randMove.second;
				// do movement
				m_board->move(fromPos, toPos);
			}
	};
	
	// This AI type will simply pick a random possible move
	class EasyAI final : public AI
	{
		public:
			EasyAI() : AI() { }
			~EasyAI() = default;

			void firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator) override;
	};

	// This AI type class implements a custom greedy action picking algorithm
	class MediumAI final : public AI
	{
		public:
			MediumAI() : AI() { }
			~MediumAI() = default;

			void firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator) override;
	};
	
	// This AI type class implements the MinMax algorithm with AB-Pruning optimization
	class HardAI final : public AI
	{
		public:
			HardAI() : AI() { }
			~HardAI() = default;

			void firePawnAction(std::shared_ptr<API::Utils::MovesGenerator>& t_moveGenerator) override;
	};

} } }
#endif !AI_HPP
