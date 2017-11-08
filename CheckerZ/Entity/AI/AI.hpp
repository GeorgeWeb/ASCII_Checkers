#ifndef MINMAX_AI_HPP
#define MINMAX_AI_HPP

#include "../Entity.hpp"

namespace CheckerZ { namespace Entity { namespace AI {

	// Base class for future types of AI
	class AI : public Entity
	{
		public: 
			AI(const std::string& t_name, const std::string& t_pawnColor) : Entity(t_name, t_pawnColor) { }
			virtual ~AI() = default;

			virtual void firePawnAction(const Position& t_posFrom, const Position& t_posTo, std::shared_ptr<API::Utils::MovesGenerator> t_moveGenerator) { }
	};
	
	// This AI type will simply pick a random possible move
	class EasyAI final : public AI
	{
		public:
			EasyAI(const std::string& t_name, const std::string& t_pawnColor) : AI(t_name, t_pawnColor) { }
			~EasyAI() = default;

			void firePawnAction(const Position& t_posFrom, const Position& t_posTo, std::shared_ptr<API::Utils::MovesGenerator> t_moveGenerator) override;
	};

	// This AI type class implements a custom greedy action picking algorithm
	class MediumAI final : public AI
	{
		public:
			MediumAI(const std::string& t_name, const std::string& t_pawnColor) : AI(t_name, t_pawnColor) { }
			~MediumAI() = default;

			void firePawnAction(const Position& t_posFrom, const Position& t_posTo, std::shared_ptr<API::Utils::MovesGenerator> t_moveGenerator) override;
	};
	
	// This AI type class implements the MinMax algorithm with AB-Pruning optimization
	class HardAI final : public AI
	{
		public:
			HardAI(const std::string& t_name, const std::string& t_pawnColor) : AI(t_name, t_pawnColor) { }
			~HardAI() = default;

			void firePawnAction(const Position& t_posFrom, const Position& t_posTo, std::shared_ptr<API::Utils::MovesGenerator> t_moveGenerator) override;
	};

} } }
#endif !MINMAX_AI_HPP
