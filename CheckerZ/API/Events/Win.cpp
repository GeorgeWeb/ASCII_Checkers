#include "Win.hpp"

namespace CheckerZ { namespace API { namespace Events {

	Win::Win() : EventFacility()
	{
		initialize();
	}

	void Win::initialize()
	{
		// Setup some values...
	}

	void Win::invoke(const std::function<void()>& t_changeTitle) const
	{
		// All the MAGIC happens in here :)	
	}

} } }