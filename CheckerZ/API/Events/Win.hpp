#ifndef WIN_HPP
#define WIN_HPP

#include "EventFacility.hpp"

namespace CheckerZ { namespace API { namespace Events {

	class Win : public EventFacility
	{
		public:
			explicit Win();
			
			void invoke(const std::function<void()>& t_changeTitle = nullptr) const override;
		
		private:
			void initialize() override;
	};

} } }

#endif !WIN_HPP