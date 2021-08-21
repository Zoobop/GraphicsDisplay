#pragma once

#include <string>
#include <fstream>

namespace DevEngine::Utils {

	class FileUtils
	{
	public:
		static std::string GetFileContents(const char* filePath)
		{
			std::ifstream in(filePath , std::ios::binary);
			if (in)
			{
				std::string contents;
				in.seekg(0, std::ios::end);
				contents.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&contents[0], contents.size());
				in.close();
				return(contents);
			}
			throw(errno);
		}
	};

}