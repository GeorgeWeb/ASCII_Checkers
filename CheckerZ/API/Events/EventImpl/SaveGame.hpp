#ifndef SAVE_GAME_HPP
#define SAVE_GAME_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	class SaveGame final : public EventFacility
	{
	public:
		explicit SaveGame();
		~SaveGame() = default;

		void invoke(std::vector<char>& t_buffer) const override;

	private:
		void initialize() override;
	};

} } } }

#endif !SAVE_GAME_HPP