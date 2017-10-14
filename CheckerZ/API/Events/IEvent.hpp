#ifndef IEVENT_HPP
#define IEVENT_HPP

#include "../../Common.hpp"

// std::includes
#include <functional>

namespace CheckerZ { namespace API { namespace Events {
	
	class IEvent
	{
		public:
			virtual ~IEvent() { };
			inline virtual void invoke(const std::function<void()>& t_func = nullptr) const
			{
				if (t_func != nullptr)
				{
					try
					{
						t_func();
					}
					catch (const std::exception& t_excep)
					{
						Logger::message(MessageType::ERR, t_excep.what());
					}
				}
			};

		private:
			IEvent() = delete;
	};

} } }

#endif !IEVENT_HPP