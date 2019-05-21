#include "script.h"

Script::Script()
{
}

Script::~Script()
{
}

bool Script::load_from_file(const std::string & dir)
{
	std::string content;
	Console::get()<<"loading            script: "<<dir<<"\n";
	
	load_content(dir, content);
	Console::get()<<content<<"\n";
	
	entry.decode(content);
	 
	return true;
}

void Script::release()
{
	entry.release();
}

void Script::load_content(const std::string& dir, std::string & cont)
{
	std::fstream file;
	file.open(dir);
	if(!file.good()) throw std::runtime_error ("cant open file: " + dir); 
	
	for(std::string buff; std::getline(file, buff);)
		cont = cont + buff;
		
	file.close();
}