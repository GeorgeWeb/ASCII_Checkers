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
	};
	
	// This AI type will simply pick a random possible move
	class SimpleAI : public AI
	{
		SimpleAI(const std::string& t_name, const std::string& t_pawnColor) : AI(t_name, t_pawnColor) { }
		~SimpleAI() = default;
	};

	// This AI type class implements the MinMax algorithm with AB-Pruning optimization
	class AdvancedAI : public AI
	{
		public:
			AdvancedAI(const std::string& t_name, const std::string& t_pawnColor) : AI(t_name, t_pawnColor) { }
			~AdvancedAI() = default;
	};
	
} } }
#endif !MINMAX_AI_HPP
