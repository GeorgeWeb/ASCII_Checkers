#ifndef TIMER_HPP
#define TIMER_HPP

// project includes
#include "../../Common.hpp"

// std::includes
#include <ctime>

namespace CheckerZ { namespace API { namespace Utils {

	// A very basic, non cross-platform timer class
	// used basically to apply delay on AI actions
	class Timer final
	{
		public:
			static Timer& getInstance()
			{
				static Timer theInstance{};
				return theInstance;
			}

			void applyTimeDelayInSeconds(double t_delayTime) const
			{
				clock_t startTime = clock(); //Start timer
				double timePassed;
				bool flag = true;

				while (flag)
				{
					timePassed = (clock() - startTime) / CLOCKS_PER_SEC;
					// stop the timer after the delayed time has passed
					if (timePassed >= t_delayTime)
						flag = false;
				}

			}
		private:
			Timer() = delete;
			Timer(const Timer&) = delete;
			Timer(Timer&&) = delete;
			Timer operator=(const Timer&) = delete;
			Timer operator=(Timer&&) = delete;
	};

} } }
#endif !TIMER_HPP
