#ifndef TAKE_ENTITY_PAWN_HPP
#define TAKE_ENTITY_PAWN_HPP

#include "../EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	class TakeEntityPawn : public EventFacility
	{
		public:
			explicit TakeEntityPawn();
			~TakeEntityPawn() = default;

			void invoke() const override;

		private:
			void initialize() override;
	};

} } } }

#endif !TAKE_ENTITY_PAWN_HPP