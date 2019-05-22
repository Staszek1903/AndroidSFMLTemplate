#include "error_generate.hpp"

void error_generate(const std::string & s)
{
	std::fstream file;
		file.open("./error.txt",std::ios::out);
		file<<s<<"\n";
		file.close();
}