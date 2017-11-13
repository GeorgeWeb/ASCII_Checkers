#include "SaveGame.hpp"
#include "../../Utils/FileIO.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	SaveGame::SaveGame()
	{

	}

	void SaveGame::initialize()
	{

	}

	void SaveGame::invoke(std::vector<char>& t_buffer) const
	{
		std::string filePath;

		Utils::Logger::message(Utils::MessageType::INF, "\t      Name your save: ", Utils::EndingDelimiter::SPACE);
		std::cin >> filePath;
		
		try
		{
			// write to the chosen file name
			Utils::FileIO::getInstance().writeFile(filePath, t_buffer);
		}
		catch (const std::exception& t_excep)
		{
			throw std::runtime_error(t_excep.what());
		}
	}

} } } }