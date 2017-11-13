#ifndef LOAD_GAME_HPP
#define LOAD_GAME_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	class LoadGame final : public EventFacility
	{
	public:
		explicit LoadGame();
		~LoadGame() = default;

		void invoke() const override;

	private:
		void initialize() override;
	};

} } } }

#endif !LOAD_GAME_HPP