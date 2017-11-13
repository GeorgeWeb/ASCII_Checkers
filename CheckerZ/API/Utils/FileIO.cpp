#include "FileIO.hpp"

namespace CheckerZ { namespace API { namespace Utils {

	bool FileIO::writeFile(const std::string& filePath, std::vector<char>& buffer)
	{
		return false;
	}

	bool FileIO::readFile(const std::string& filePath, std::vector<char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);

		// error checking the path
		if (file.fail())
		{
			throw std::runtime_error("Error finding path: " + filePath);
			return false;
		}

		// seek to the end
		file.seekg(0, std::ios::end);

		// get the file size
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		// reduce the file size by any header bytes (if present)
		fileSize -= file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);

		file.close();

		return true;
	}

} } }
