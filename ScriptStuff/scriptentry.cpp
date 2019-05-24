#include "scriptentry.h"

ScriptEntry::ScriptEntry()
    : value(nullptr)
{}

ScriptEntry::~ScriptEntry()
{
    release();
}

void ScriptEntry::decode(std::string data)
{	
    // pojedyncze value bez labela nie dzialają i nested arraye... też nie dzialają
	Console::get()<<data<<"\n";
    if(Parser::get_last_non_whitespace(data) != ';')
        throw std::runtime_error("entry not terminated with ';'");
    name = decode_name(data);
    std::string v = decode_value(data);
	
    if(Parser::is_array(v))
		value = new ValueArray(v);
    else if(Parser::is_int(v))
	{
		value = new ValueInt(v);
		Console::get()<< get_int_value() << "\n";
	}
    else if(Parser::is_float(v))
    {
		value = new ValueFloat(v);
		Console::get()<< get_float_value() << "\n";
	}
    else if(Parser::is_string(v))
    {
		value = new ValueString(v);
		Console::get()<< get_string_value() << "\n";
	}
    else throw std::runtime_error("cannot identifie value type \n<" + v+">");
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
    if(!value)
        throw std::runtime_error("value not initialized");

    if(value->type != Value::INT)
        throw std::runtime_error("value not of value INT");
    ValueInt * v = static_cast<ValueInt*>(value);
    return  v->val;
}

float ScriptEntry::get_float_value()
{
    if(!value)
        throw std::runtime_error("value not initialized");

    if(value->type != Value::FLOAT)
        throw std::runtime_error("value not of value INT");
    ValueFloat * v = static_cast<ValueFloat*>(value);
    return  v->val;
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

void ScriptEntry::release()
{
    Value * temp = value;
    value = nullptr;
    if(temp != nullptr)
        delete temp;
}

std::string ScriptEntry::decode_name(const std::string &data)
{
    size_t label_end_pos = data.find(':');

    if(label_end_pos == std::string::npos)
        return "";
    else if(label_end_pos == 0)
        throw std::runtime_error("expected label before ':'");
    else
    {
        auto label = data.substr(0,label_end_pos);
        Parser::erase_whitespaces(label);
        if(label.size() > 0)
            return label;
        else
            throw std::runtime_error(" label must be a valid string");
    }
}

std::string ScriptEntry::decode_value(const std::string &data)
{
    size_t val_pos = data.find(':');
    if(val_pos == std::string::npos) val_pos = -1;
    size_t end_pos = data.find_last_of(';');
    if(end_pos== std::string::npos)
        throw std::runtime_error("expecting ';' at end of value");
    if(val_pos+1 >= end_pos)
        throw std::runtime_error("expecting value in entry");

    return data.substr(val_pos+1, end_pos-(val_pos+1));
}

ValueInt::ValueInt(const std::string &data)
    :Value(Value::INT)
{
	if(Parser::is_decimal(data))
	    val = Parser::get_int(data);
	else if(Parser::is_binary(data))
	    val = Parser::get_bin_int(data);
	else if(Parser::is_hex(data))
	    val = Parser::get_hex_int(data);
	else 
	    throw std::runtime_error("cannot identify int format");
}

ValueFloat::ValueFloat(const std::string &data)
    : Value(Value::FLOAT), val(Parser::get_float(data)) {}

ValueString::ValueString(const std::string &data)
    : Value(Value::STRING), val(Parser::get_string(data)){}

ValueArray::ValueArray(const std::string &data)
    : Value(Value::ARRAY)
{
    auto svec = Parser::get_array(data);
    val.resize(svec.size());
    for(size_t i=0; i<val.size();++i)
        val.at(i).decode(svec.at(i));
}