#ifndef S_LOGGER_HPP
#define S_LOGGER_HPP

// std::includes
#include <iostream>
#include <exception>

namespace CheckerZ { namespace API {
	
	enum MessageType
	{
		INF,	///> normal informational message
		ERR		///> an error message
	};

	class Logger
	{
		public:
			static void message(const MessageType& const t_msgType, const char* t_msg)
			{
				if (t_msgType == MessageType::INF)
				{
					std::cout << t_msg << "\n";
				}
				else if (t_msgType == MessageType::ERR)
				{
					std::cout << t_msg << "\n";
				}
				else
				{
					std::cerr << "An invalid argument is passed Logger::message(messageType, messsage)\n";
					exit(EXIT_FAILURE);
					return;
				}
			}
	};

} }

#endif !S_LOGGER_HPP