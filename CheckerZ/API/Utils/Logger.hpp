#ifndef S_LOGGER_HPP
#define S_LOGGER_HPP

// std::includes
#include <iostream>
#include <exception>
#include <string>

namespace CheckerZ { namespace API { namespace Utils {

	enum class MessageType : uint8
	{
		INF,	///> normal informational message
		ERR		///> an error message
	};

	enum class EndingDelimiter : uint8
	{
		NONE = 0,
		SPACE = ' ',
		NLINE = '\n'
	};

	class Logger final
	{
		public:
			// Without parameter
			static void message(MessageType t_msgType, const std::string& t_msg, EndingDelimiter t_end = EndingDelimiter::NLINE)
			{
				if (t_msgType == MessageType::INF)
				{
					std::cout << t_msg << static_cast<uint8>(t_end);
				}
				else if (t_msgType == MessageType::ERR)
				{
					std::cout << t_msg << static_cast<uint8>(t_end);
				}
				else
				{
					std::cerr << "An invalid argument is passed Logger::message(messageType, messsage)\n";
					exit(EXIT_FAILURE);
					return;
				}
			}
			// With parameter
			static void message(MessageType t_msgType, const std::string& t_msg, const std::string& t_param, EndingDelimiter t_end = EndingDelimiter::NLINE)
			{
				if (t_msgType == MessageType::INF)
				{
					std::cout << t_msg << t_param << static_cast<uint8>(t_end);
				}
				else if (t_msgType == MessageType::ERR)
				{
					std::cout << t_msg << t_param << static_cast<uint8>(t_end);
				}
				else
				{
					std::cerr << "An invalid argument is passed Logger::message(messageType, messsage)\n";
					exit(EXIT_FAILURE);
					return;
				}
			}
	};

} } }

#endif !S_LOGGER_HPP