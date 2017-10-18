#ifndef WIN_GAME_HPP
#define WIN_GAME_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	class WinGame : public EventFacility
	{
		public:
			explicit WinGame();
			~WinGame() = default;

			void invoke() const override;

		private:
			void initialize() override;
	};

} } } }

#endif !WIN_GAME_HPP