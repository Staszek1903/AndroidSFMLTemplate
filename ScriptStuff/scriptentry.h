#ifndef SCRIPT_ENTRY_H_
#define SCRIPT_ENTRY_H_

#include <string>
#include <vector>
#include <exception>
#include <memory>
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
    std::unique_ptr<Value> value;
	
public:
	ScriptEntry();
    ScriptEntry(const ScriptEntry & other);
	~ScriptEntry();
	/**
        * decodes entry from string and entries inside of it recursively
		* @param data - string to decode
		* @throw runtime_error on failure
		*/
	void decode(std::string data);
	
	/**
		* @return name of the entry
		*/
    const std::string & get_name() const;
	/**
		* @return type od entry value
		*/
    unsigned int get_value_type() const;
	
	/**
		* @throw runtime_error when entry is not of correct type
		* @return value array of entries
		*/
    const std::vector<ScriptEntry> & get_array_value() const;
	/**
		* @throw runtime_error when entry is not of correct type
		* @return value int
		*/
    int get_int_value() const;
	/**
		* @throw runtime_error when entry is not of correct type
		* @return value float
		*/
    float get_float_value() const;
	/**
		* @throw runtime_error when entry is not of correct type
		* @return value string
		*/
    const std::string & get_string_value() const;

    /**
     * @brief at return entry in array value of index
     * @param index
     * @return entry
     */
    const ScriptEntry & at(size_t index) const;

    /**
     * @brief at return first entry that contains the name label
     * @param label name to search for
     * @return entry
     */
    const ScriptEntry & at(const std::string & label) const;
	
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
    ValueInt(const Value & other);
	int val;

};

class ValueFloat : public Value
{
public:
    ValueFloat(const std::string & data);
    ValueFloat(const Value & other);
	float val;
};

class ValueString: public Value
{
public:
    ValueString(const std::string & data);
    ValueString(const Value & other);
	std::string val;
};

class ValueArray: public Value
{
public:
    ValueArray(const std::string & data);
    ValueArray(const Value &other);
 	std::vector<ScriptEntry> val;
};	

#endif
