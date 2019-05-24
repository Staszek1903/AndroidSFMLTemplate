#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <array>
#include <sstream>
#include <vector>

class Parser
{
    static constexpr std::array<char,16> hex_digits = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

    Parser();
public:
    /**
        * check if string contains value of type
        * @return if so
        */
    static bool is_int(const std::string & val);
    static bool is_decimal(std::string val);
    static bool is_binary(std::string val);
    static bool is_hex(std::string val);

    /**
        * check if string contains value of type
        * @return if so
        */
    static bool is_float(std::string val);

    /**
        * check if string contains value of type
        * @return if so
        */
    static bool is_string(std::string val);

    /**
        * check if string contains value of type
        * @return if so
        */
    static bool is_array(std::string val);

    /**
        * erases whitespaces in given tring
        * @param s - given string
        */
    static void erase_whitespaces(std::string & s);

    static bool is_containing(const char * data, size_t size, char elem);

    static int get_int(std::string val);
    
    static int get_hex_int(std::string val);
    
    static int get_bin_int(std::string  val);

    static float get_float(std::string val);

    static std::string get_string(std::string val);

    static std::vector<std::string> get_array(std::string val);

    static char get_first_non_whitespace(const std::string & s);

    static char get_last_non_whitespace(const std::string & s);
};

#endif // PARSER_H