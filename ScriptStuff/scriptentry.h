#ifndef SCRIPT_ENTRY_H_
#define SCRIPT_ENTRY_H_

#include <string>
#include <vector>
#include <exception>
#include "../console.h"

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
		* erases whitespaces in given tring
		* @param s - given string
		*/
	void erase_whitespaces(std::string & s);
	
	/**
		* destructs content
		*/
	void release();
	
private:
	/**
		* check if string contains value of type
		* @return if so
		*/
	bool is_int(std::string val);
	/**
		* check if string contains value of type
		* @return if so
		*/
	bool is_float(std::string val);
	/**
		* check if string contains value of type
		* @return if so
		*/
	bool is_string(std::string val);
	/**
		* check if string contains value of type
		* @return if so
		*/
	bool is_array(std::string val);
	
	/**
		* @return position of last ';'
		* @throw runtime_eror if ';' is not last non whitespace character
		*/
	size_t find_terminate(const std::string & s);
};
	

class ValueInt : public Value
{
public:
	ValueInt(const std::string & data) :Value(Value::INT){}	
	int val;
};

class ValueFloat : public Value
{
public:
	ValueFloat(const std::string & data): Value(Value::FLOAT){}
	float val;
};

class ValueString: public Value
{
public:
	ValueString(const std::string & data): Value(Value::STRING){}
	std::string val;
};

class ValueArray: public Value
{
public:
 	ValueArray(const std::string & data): Value(Value::ARRAY){}
 	std::vector<ScriptEntry> val;
};	

#endif