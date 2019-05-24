#ifndef SCRIPT_ENTRY_H_
#define SCRIPT_ENTRY_H_

#include <string>
#include <vector>
#include <exception>
#include "../console.h"
#include "parser.h"

class Value
{
public:
	Value(unsigned int type) :type(type){}
	
	unsigned int type;
	enum
	{
		INT,
		FLOAT,
		STRING,
		ARRAY,
	};
};

class ScriptEntry
{
	std::string name;
	Value * value;
	
public:
	ScriptEntry();
	~ScriptEntry();
	/**
		* decodes entry from string and entrirs inside of it recursively
		* @param data - string to decode
		* @throw runtime_error on failure
		*/
	void decode(std::string data);
	
	/**
		* @return name of the entry
		*/
	const std::string & get_name();
	/**
		* @return type od entry value
		*/
	unsigned int get_value_type();
	
	/**
		* @throw runtime_error when entry is not of correct type
		* @return value array of entries
		*/
	const std::vector<ScriptEntry> & get_array_value();
	/**
		* @throw runtime_error when entry is not of correct type
		* @return value int
		*/
	int get_int_value();
	/**
		* @throw runtime_error when entry is not of correct type
		* @return value float
		*/
	float get_float_value();
	/**
		* @throw runtime_error when entry is not of correct type
		* @return value string
		*/
	const std::string & get_string_value();
	
	/**
		* destructs content
		*/
	void release();

private:
    std::string decode_name(const std::string & data );
    std::string decode_value(const std::string & data );
};
	

class ValueInt : public Value
{
public:
    ValueInt(const std::string & data);
	int val;

};

class ValueFloat : public Value
{
public:
    ValueFloat(const std::string & data);
	float val;
};

class ValueString: public Value
{
public:
    ValueString(const std::string & data);
	std::string val;
};

class ValueArray: public Value
{
public:
    ValueArray(const std::string & data);
 	std::vector<ScriptEntry> val;
};	

#endif