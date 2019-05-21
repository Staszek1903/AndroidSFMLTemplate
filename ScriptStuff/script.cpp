#include "script.h"

Script::Script()
{
}

Script::~Script()
{
}

bool Script::load_from_file(const std::string & dir)
{
	
	Console::get()<<"loading            script: "<<dir<<"\n";
	
	Console::get()<<content<<"\n";
	
	Paser pars;
	pars.load(content);
	
		
				
	file.close(); 
	return false;
}

void Script::release()
{
	
}

void load_content(std::string & cont)
{
	std::fstream file;
	file.open(dir);
	if(!file.good()) throw std::runtime_error ("cant open file: " + dir); 
	
	for(std::string buff; std::getline(file, buff);)
		cont = cont + buff;
}