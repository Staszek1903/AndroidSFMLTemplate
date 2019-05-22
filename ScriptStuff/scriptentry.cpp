#include "scriptentry.h"

ScriptEntry::ScriptEntry()
{}

ScriptEntry::~ScriptEntry()
{}

void ScriptEntry::decode(std::string data)
{
	
	erase_whitespaces(data);
	
	Console::get()<<data<<"\n";
	size_t terminate_pos = find_terminate(data);
	size_t label_end_pos = data.find(':');
	size_t val_begin_pos =0;
	if(terminate_pos == std::string::npos)
		throw std::runtime_error("lacking ';' at end of entry;");
	
	if(label_end_pos == std::string::npos)
	{
		name = "";
	}
	else
	{
		val_begin_pos = label_end_pos+1;
		if(val_begin_pos >= data.size()) 
		throw std::runtime_error(" no value after ':'");
		auto label = data.substr(0,label_end_pos);
		if(is_string(label))
			this->name = label;
		else
			throw std::runtime_error(" label must be a valid string");
	}
	
	return;
	
	auto v = data.substr(val_begin_pos, data.size() - val_begin_pos);
	
	if(is_array(v))
		value = new ValueArray(v);
	if(is_int(v))
		value = new ValueInt(v);
	else if(is_float(v))
		value = new ValueFloat(v);
	else if(is_string(v))
		value = new ValueString(v);
	else throw std::runtime_error("cannot indentifie value type");
}

const std::string & ScriptEntry::get_name()
{
	return this->name;
}

unsigned int ScriptEntry::get_value_type()
{
	if(!value)
		throw std::runtime_error("value not initialized");
	return value->type;
}	

const std::vector<ScriptEntry> & ScriptEntry::get_array_value()
{
	if(!value)
		throw std::runtime_error("value not initialized");
		
	if(value->type != Value::ARRAY)
		throw std::runtime_error("value not of value ARRAY");
	ValueArray * v = static_cast<ValueArray*> (value);
	return v->val;	
}	

int ScriptEntry::get_int_value()
{
	return 0;
}

float ScriptEntry::get_float_value()
{
	return 0.0f;
}

const std::string & ScriptEntry::get_string_value()
{
	if(!value)
		throw std::runtime_error("value not initialized");
		
	if(value->type != Value::STRING)
		throw std::runtime_error("value not of value STRING");
	ValueString * v = static_cast<ValueString*> (value);
	
	return v->val;
}

void ScriptEntry::erase_whitespaces(std::string & s)
{
	std::string n  ="";
	for(char a : s)
	{
		if(a != ' ' && a != '\t' && a != '\n')
			n = n + a;
	}
	
	s = n; 
}

bool ScriptEntry::is_int(std::string val)
{
	return false;
}

bool ScriptEntry::is_float(std::string val)
{return false;}

bool ScriptEntry::is_string(std::string val)
{return false;}	

bool ScriptEntry::is_array(std::string val)
{return false;}

void ScriptEntry::release()
{}

size_t ScriptEntry::find_terminate(const std::string & s)
{
	for(int i= s.size()-1; i>=0; ++i)
		if(s.at(i) == ';') return i;
		else if(!std::iswspace(s.at(i))) throw std::runtime_error("garbage at and of line");

	throw std::runtime_error(" ';' not fount at and of entry");
}