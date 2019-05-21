#ifndef SCRIPT_H_
#define SCRIPT_H_

#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
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

class Value
{
public:
	Value(std::size_t type) :type(type){}
	
	size_t type;
	enum
	{
		INT,
		FLOAT,
		STRING,
		ARRAY,
	};
};

typedef std::pair < std::string, Value* > Entry;

class ValueInt : public Value
{
public:
	ValueInt() :Value(Value::INT){}	
	int val;
};

class ValueFloat : public Value
{
public:
	ValueFloat(): Value(Value::FLOAT){}
	float val;
};

class ValueArray: public Value
{
public:
 	ValueArray(): Value(Value::ARRAY){}
 	std::vector<Entry> array;
};	

class Script
{
	bool loaded = false;
	
	std::vector<Entry> content;
	
public:
	Script();
	~Script();
	
	bool load_from_file(const std::string & dir);
	void release();
	
	//getters
private:
	void load_content(std::string & cont);
};
	
#endif