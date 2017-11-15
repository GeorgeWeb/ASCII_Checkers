#include "SaveGame.hpp"
#include "../../Utils/FileIO.hpp"
#include <windows.h>

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	SaveGame::SaveGame()
	{

	}

	void SaveGame::initialize()
	{

	}

	void SaveGame::invoke(std::vector<char>& t_buffer, const std::string& t_outputFile) const
	{
		std::string outputDir;
		Utils::Logger::message(Utils::MessageType::INF, "\t      Name your save: ", Utils::EndingDelimiter::SPACE);
		std::cin >> outputDir;
		
		std::string fullOutputDir = "saves/" + outputDir;
		// create directory named after the save name (if not exists)
		if (CreateDirectory(fullOutputDir.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{
			try
			{
				// write to the chosen file name
				Utils::FileIO::getInstance().writeFile(fullOutputDir + "/" + t_outputFile, t_buffer);
			}
			catch (const std::exception& t_excep)
			{
				throw std::runtime_error(t_excep.what());
			}
		}
		else
		{
			throw std::runtime_error("\t      Error: a save with this name already exists.");
		}
	}

} } } }