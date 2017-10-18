#ifndef S_LOGGER_HPP
#define S_LOGGER_HPP

// std::includes
#include <iostream>
#include <exception>
#include <string>

namespace CheckerZ { namespace API {
	
	enum class MessageType : uint8
	{
		INF,	///> normal informational message
		ERR		///> an error message
	};

	class Logger
	{
		public:
			static void message(const MessageType& const t_msgType, const std::string& t_msg, const std::string& t_param = "")
			{
				if (t_msgType == MessageType::INF)
				{
					std::cout << t_msg << t_param << "\n";
				}
				else if (t_msgType == MessageType::ERR)
				{
					std::cout << t_msg << t_param << "\n";
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