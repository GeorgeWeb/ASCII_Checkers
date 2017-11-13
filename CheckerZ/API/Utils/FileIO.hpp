#ifndef FILEIO_HPP
#define FILEIO_HPP

// std::includes
#include <string>
#include <vector>
#include <fstream>

namespace CheckerZ { namespace API { namespace Utils {

	// Singleton File handling API
	class FileIO final
	{
	public:
		static FileIO& getInstance()
		{
			static FileIO theInstance{};
			return theInstance;
		}

		void writeFile(const std::string& filePath, std::vector<char>& buffer);
		void readFile(const std::string& filePath, std::vector<char>& buffer);

	private:
		FileIO() = delete;
		FileIO(const FileIO&) = delete;
		FileIO(FileIO&&) = delete;
		FileIO operator=(const FileIO&) = delete;
		FileIO operator=(FileIO&&) = delete;
	};

} } }

#endif !FILEIO_HPP