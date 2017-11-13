#include "LoadGame.hpp"
#include "../../Utils/FileIO.hpp"

namespace CheckerZ { namespace API { namespace Events { namespace EventImpl {

	LoadGame::LoadGame()
	{

	}

	void LoadGame::initialize()
	{

	}

	void LoadGame::invoke(std::vector<char>& t_buffer) const
	{
		try
		{
			Utils::FileIO::getInstance().readFile("example.txt", t_buffer);
		}
		catch (const std::exception& t_excep)
		{
			throw std::runtime_error(t_excep.what());
		}
	}

} } } }