#ifndef SCRIPT_H_
#define SCRIPT_H_

#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include "scriptentry.h"
#include "../console.h"
/*
vname :
{
	snam :val;
	snam2 : val2;
	val3;
	val4;
	val5;
	snam3 : 
	{
		ssnam1 : sval1
		ssnam2 : sval 2;
		ssnam3 : { 1;2;3;4;5 }
	}
}
*/	

class Script
{
	bool loaded = false;
	
	ScriptEntry entry;
	
public:
	Script();
	~Script();
	
	/**
		* loads and parses file
		* @param dir - directory of file
		* @return bool - succes
		*/
	bool load_from_file(const std::string & dir);
	/**
		* destroys content of script
		*/
	void release();
	
	//getters
private:
	
	void load_content(const std::string & dir, std::string & cont);
};
	
#endif