#ifndef WIN_GAME_HPP
#define WIN_GAME_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	class WinGame final : public EventFacility
	{
		public:
			explicit WinGame();
			~WinGame() = default;

			void invoke(GameSystemState& t_finalGameState, std::shared_ptr<Board>& t_board, const std::shared_ptr<Entity::Entity>& t_player) const override;

		private:
			void initialize() override;
	};

} } } }

#endif !WIN_GAME_HPP