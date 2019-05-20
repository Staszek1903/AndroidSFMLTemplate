#ifndef SCRIPT_H_
#define SCRIPT_H_

class Script
{
	bool loaded = false;
	
	// Script contents
	
public:
	Script();
	~Scpript();
	
	bool load_from_file(std::string dir);
	void release;
	
	//getters
	
};
	