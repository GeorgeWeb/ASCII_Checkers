#ifndef GAME_HELPER_HPP
#define GAME_HELPER_HPP

#include "../../Common.hpp"
#include <functional>

namespace CheckerZ { namespace API { namespace Utils {
	
	class BoardHelper
	{
		public:
			static void traverse(std::function<void(uint16)> t_action)
			{
				for (uint16 i = 0; i < 2 << 3; i++)		///> 8
					for (uint16 j = 0; j < 2 << 3; j++) ///> 64
						std::invoke(t_action, j);
			}
	};

} } }
#endif !GAME_HELPER_HPP