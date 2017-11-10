#ifndef TIMER_HPP
#define TIMER_HPP

// project includes
#include "../../Common.hpp"

// std::includes
#include <ctime>

namespace CheckerZ { namespace API { namespace Utils {

	// A very basic, non cross-platform timer class
	// used basically to apply delay on AI actions
	class Timer
	{
		public:
			static void applyTimeDelayInSeconds(double delayTime)
			{
				clock_t startTime = clock(); //Start timer
				double timePassed;
				bool flag = true;

				while (flag)
				{
					timePassed = (clock() - startTime) / CLOCKS_PER_SEC;
					// stop the timer after the delayed time has passed
					if (timePassed >= delayTime)
						flag = false;
				}

			}
		private:
			Timer() = delete;
	};

} } }
#endif !TIMER_HPP
