#include "parser.h"

constexpr std::array<char,16> Parser::hex_digits;

Parser::Parser()
{

}

bool Parser::is_int(const std::string &val)
{
    return (is_decimal(val) || is_hex(val) || is_binary(val));
}

bool Parser::is_decimal(std::string val)
{
    erase_whitespaces(val);
    if(val.size() == 0) return false;
    for(char a: val)
        if(!std::isdigit(a)) return false;
    return true;
}

bool Parser::is_binary(std::string val)
{
    erase_whitespaces(val);
    if(val.size() < 3) return false;
    if(val.at(0) != '0' || val.at(1) != 'b') return false;

    for(size_t i=2; i<val.size(); ++i)
    {
        char a = val.at(i);
        if(a != '0' && a != '1') return false;
    }

    return true;
}

bool Parser::is_hex(std::string val)
{
    erase_whitespaces(val);
    if(val.size() < 3) return false;
    if(val.at(0) != '0' || val.at(1) != 'x') return false;

    for(size_t i=2; i<val.size(); ++i)
    {
        char a = val.at(i);
        if(!is_containing(hex_digits.data(), hex_digits.size(), a)) return false;
    }

    return true;
}

bool Parser::is_float(std::string val)
{
    erase_whitespaces(val);
    if(val.size() < 3) return false;
    size_t point_pos = val.find('.');
    if(point_pos == std::string::npos) return false;
    if(point_pos == val.size()-1) return false;
    if(val.find('.', point_pos+1) != std::string::npos) return false;

    return (is_decimal(val.substr(0,point_pos)) && is_decimal(val.substr(point_pos+1, val.size()- point_pos)));
}

bool Parser::is_string(std::string val)
{
    erase_whitespaces(val);
    if(val.size() < 2) return false;
    if(val.at(0) != '"' || val.at(val.size()-1) != '"') return false;
    return true;
}

bool Parser::is_array(std::string val)
{
    erase_whitespaces(val);
    if(val.at(0) != '{' || val.at(val.size()-1) != '}') return false;
    return true;
}

void Parser::erase_whitespaces(std::string &s)
{
    std::string n  ="";
    for(char a : s)
    {
        if(a != ' ' && a != '\t' && a != '\n')
            n = n + a;
    }

    s = n;
}

bool Parser::is_containing(const char *data, size_t size, char elem)
{
    for(size_t i=0; i<size; ++i)
    {
        if(data[i] == elem ) return true;
    }

    return false;
}

int Parser::get_int(std::string val)
{
    if(!is_int(val)) throw std::runtime_error("value is not int");
    erase_whitespaces(val);
    std::stringstream ss(val);
    int ret;
    ss>>ret;
    return ret;
}

float Parser::get_float(std::string val)
{
    if(!is_float(val)) throw std::runtime_error("value is not float");
    erase_whitespaces(val);
    std::stringstream ss(val);
    int ret;
    ss>>ret;
    return ret;
}

std::string Parser::get_string(std::string val)
{
    if(!is_string(val)) throw std::runtime_error("value is not string");
    size_t begin = val.find_first_of('"');
    size_t end = val.find_last_of('"');
    if(begin+1 >= end) throw std::runtime_error(" value is not a string" );
    return  val.substr(begin+1, end-(begin+1));
}

std::vector<std::string> Parser::get_array(std::string val)
{
    if(!is_array(val)) throw std::runtime_error("value is not array");
    std::vector<std::string> arr;

    erase_whitespaces(val);
    std::string content = val.substr(1, val.size()-2);

    size_t pos = 0;
    while(1)
    {
        size_t last_pos = pos;
        if(pos+1 >= val.size()) break;
        pos = val.find(';',pos+1);
        if(pos == std::string::npos)
            break;

        arr.push_back(val.substr(last_pos+1, pos-last_pos));
    }

    return arr;
}

char Parser::get_first_non_whitespace(const std::string &s)
{
    for(size_t i=0; i<s.size(); ++i)
    {
        wint_t a = static_cast<wint_t>(s.at(i));
        if(!iswspace(a)) return  s.at(i);
    }

    throw std::runtime_error(" string does not contain any non whitespace characters");
}

char Parser::get_last_non_whitespace(const std::string &s)
{
    for(size_t i= s.size()-1; i<s.size(); --i)
    {
        wint_t a = static_cast<wint_t>(s.at(i));
        if(!iswspace(a)) return  s.at(i);
    }

    throw std::runtime_error(" string does not contain any non whitespace characters");
}
