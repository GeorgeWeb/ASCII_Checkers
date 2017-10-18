#ifndef LOSE_GAME_HPP
#define LOSE_GAME_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	class LoseGame : public EventFacility
	{
		public:
			explicit LoseGame();
			~LoseGame() = default;

			void invoke() const override;

		private:
			void initialize() override;
	};

} } } }

#endif !LOSE_GAME_HPP