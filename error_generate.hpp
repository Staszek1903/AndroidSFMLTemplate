#ifndef ERROR_GENERATE_HPP_
#define ERROR_GENERATE_HPP_
#include <fstream>

void error_generate(const std::string & s)
{
	std::fstream file;
		file.open("./error.txt",std::ios::out);
		file<<s<<"\n";
		file.close();
}

#endif