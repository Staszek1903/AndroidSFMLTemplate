#ifndef SCRIPT_H_
#define SCRIPT_H_

#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include "scriptentry.h"
#include "../IOStuff/console.h"

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
	

    const ScriptEntry &getEntry() const;

private:

    void load_content(const std::string & dir, std::string & cont);
};
	
#endif
