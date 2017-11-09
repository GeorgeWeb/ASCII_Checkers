#ifndef QUIT_GAME_HPP
#define QUIT_GAME_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl{

	class QuitGame final : public EventFacility
	{
		public:
			explicit QuitGame();
			~QuitGame() = default;

			void invoke() const override;

		private:
			void initialize() override;
	};

} } } }

#endif !QUIT_GAME_HPP