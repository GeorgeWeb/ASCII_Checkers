#include "FileIO.hpp"

namespace CheckerZ { namespace API { namespace Utils {

	void FileIO::writeFile(const std::string& filePath, std::vector<char>& buffer)
	{
		// open file for writing (binary mode)
		std::ofstream file(filePath, std::ios::binary);
		
		// error checking the path
		if (file.fail())
			throw std::runtime_error("Error finding path: " + filePath);

		// write to the file
		file.write((char*)&(buffer[0]), buffer.size());

		// handle memory
		file.close();
	}

	void FileIO::readFile(const std::string& filePath, std::vector<char>& buffer)
	{
		// open file for reading (binary mode)
		std::ifstream file(filePath, std::ios::binary);

		// error checking the path
		if (file.fail())
			throw std::runtime_error("Error finding path: " + filePath);

		// get the file size
		file.seekg(0, std::ios::end);
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		// reduce the file size by any header bytes (if present)
		fileSize -= file.tellg();
		buffer.resize(fileSize);
		
		// read from the file
		file.read((char*)&(buffer[0]), fileSize);

		// handle memory
		file.close();
	}

} } }
