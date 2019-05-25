#include "scriptentry.h"

ScriptEntry::ScriptEntry()
{}

ScriptEntry::ScriptEntry(const ScriptEntry &other)
    :name(other.name)
{
    Value * tempv = other.value.get();
    switch (tempv->type)
    {
    case Value::INT   : value = std::make_unique<ValueInt>(*tempv);     break;
    case Value::FLOAT : value = std::make_unique<ValueFloat>(*tempv);   break;
    case Value::STRING: value = std::make_unique<ValueString>(*tempv);  break;
    case Value::ARRAY : value = std::make_unique<ValueArray>(*tempv);   break;
    default:
        value.reset();
        break;
    }
}

ScriptEntry::~ScriptEntry()
{
    release();
}

void ScriptEntry::decode(std::string data)
{	
    // pojedyncze value bez labela nie dzialają i nested arraye... też nie dzialają
    if(Parser::get_last_non_whitespace(data) != ';')
        throw std::runtime_error("entry not terminated with ';'");
    name = decode_name(data);
    Console::get()<<"name: <"<<name<<">\n";
    std::string v = decode_value(data);
	
    if(Parser::is_array(v))
    {
        Console::get()<<"array:\n";
        value = std::make_unique<ValueArray>(v);
    }
    else if(Parser::is_int(v))
	{
        value = std::make_unique<ValueInt>(v);
        Console::get()<< "value: <"<<get_int_value() << ">\n";
	}
    else if(Parser::is_float(v))
    {
        value = std::make_unique<ValueFloat>(v);
        Console::get()<<"value: <"<< get_float_value() << ">\n";
	}
    else if(Parser::is_string(v))
    {
        value = std::make_unique<ValueString>(v);
        Console::get()<< "value <"<<get_string_value() << ">\n";
	}
    else throw std::runtime_error("cannot identifie value type \n<" + v+">");
}

const std::string & ScriptEntry::get_name() const
{
	return this->name;
}

unsigned int ScriptEntry::get_value_type() const
{
	if(!value)
		throw std::runtime_error("value not initialized");
	return value->type;
}	

const std::vector<ScriptEntry> & ScriptEntry::get_array_value() const
{
	if(!value)
		throw std::runtime_error("value not initialized");
		
	if(value->type != Value::ARRAY)
		throw std::runtime_error("value not of value ARRAY");
    ValueArray * v = static_cast<ValueArray*> (value.get());
	return v->val;	
}	

int ScriptEntry::get_int_value() const
{
    if(!value)
        throw std::runtime_error("value not initialized");

    if(value->type != Value::INT)
        throw std::runtime_error("value not of value INT");
    ValueInt * v = static_cast<ValueInt*>(value.get());
    return  v->val;
}

float ScriptEntry::get_float_value() const
{
    if(!value)
        throw std::runtime_error("value not initialized");

    if(value->type != Value::FLOAT)
        throw std::runtime_error("value not of value INT");
    ValueFloat * v = static_cast<ValueFloat*>(value.get());
    return  v->val;
}

const std::string & ScriptEntry::get_string_value() const
{
	if(!value)
		throw std::runtime_error("value not initialized");
		
	if(value->type != Value::STRING)
		throw std::runtime_error("value not of value STRING");
    ValueString * v = static_cast<ValueString*> (value.get());
	
    return v->val;
}

const ScriptEntry &ScriptEntry::at(size_t index) const
{
    return get_array_value().at(index);
}

const ScriptEntry &ScriptEntry::at(const std::string &label) const
{
    const auto & v = get_array_value();
    for(const auto & e : v)
    {
        if(e.get_name() == label)
            return e;
    }

    throw std::runtime_error("cant find etry with label: <"+label+">");
}

void ScriptEntry::release()
{
    value.reset();
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
    if(val_pos == std::string::npos) val_pos = static_cast<size_t>(-1);
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

ValueInt::ValueInt(const Value &other)
    :Value(Value::INT), val(static_cast<const ValueInt*>(&other)->val)
{}

ValueFloat::ValueFloat(const std::string &data)
    : Value(Value::FLOAT), val(Parser::get_float(data)) {}

ValueFloat::ValueFloat(const Value &other)
    : Value(Value::INT), val(static_cast<const ValueFloat *>(&other)->val)
{}

ValueString::ValueString(const std::string &data)
    : Value(Value::STRING), val(Parser::get_string(data)){}

ValueString::ValueString(const Value &other)
    : Value(Value::INT), val(static_cast<const ValueString *>(&other)->val)
{}

ValueArray::ValueArray(const std::string &data)
    : Value(Value::ARRAY)
{
    auto svec = Parser::get_array(data);
    val.resize(svec.size());
    for(size_t i=0; i<val.size();++i)
        val.at(i).decode(svec.at(i));
}

ValueArray::ValueArray(const Value &other)
    : Value(Value::INT), val(static_cast<const ValueArray *>(&other)->val)
{}
