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
     * @brief is_int check if string contains value of type int. Ignores whitespaces.
     * @param val string
     * @return if so
     */

    static bool is_int(const std::string & val);
    /**
     * @brief is_decimal check if string contains decimal integer. Ignores whitespaces.
     * @param val string
     * @return if so
     */
    static bool is_decimal(std::string val);

    /**
     * @brief is_binary checks if strng contains binary number. Ignores whitespaces.
     * @param val string
     * @return if so
     */
    static bool is_binary(std::string val);

    /**
     * @brief is_hex checks of string contains hex number. Ignores whitespaces.
     * @param val
     * @return
     */
    static bool is_hex(std::string val);

    /**
     * @brief is_float checks if string contains value of type float
     * @param val string
     * @return if so
     */
    static bool is_float(std::string val);

    /**
     * @brief is_string check if string contains value of type string
     * @param val string
     * @return if so
     */
    static bool is_string(std::string val);

    /**
     * @brief is_array check if string contains value of type
     * @param val string
     * @return if so
     */
    static bool is_array(std::string val);

    /**
     * @brief erase_whitespaces erases whitespaces in given tring
     * @param s - given string
     */
    static void erase_whitespaces(std::string & s);

    /**
     * @brief is_containing checks if char array contains maching element
     * @param data pointer to array
     * @param size size of array
     * @param elem element to match
     * @return if so
     */
    static bool is_containing(const char * data, size_t size, char elem);

    /**
     * @brief get_int converts string containing decimal integer into int
     * @param val string
     * @return integer value
     */
    static int get_int(std::string val);
    
    /**
     * @brief get_hex_int converts string containing hex integer into int
     * @param val string
     * @return integer value
     */
    static int get_hex_int(std::string val);
    
    /**
     * @brief get_bin_int converts string containing binary intrger into int
     * @param val string
     * @return integer value
     */
    static int get_bin_int(std::string  val);

    /**
     * @brief get_float converts string containing float value into float
     * @param val string
     * @return float value
     */
    static float get_float(std::string val);

    /**
     * @brief get_string converts string containing string value into string
     * @param val string
     * @return string value
     */
    static std::string get_string(std::string val);

    /**
     * @brief get_array parses array into separate entries separatet by ';'
     * @param val string
     * @return vector of entries
     */
    static std::vector<std::string> get_array(std::string val);

    /**
     * @brief get_first_non_whitespace searches for first non whitespace character in string
     * @param s string
     * @return first non whitespace character
     */
    static char get_first_non_whitespace(const std::string & s);

    /**
     * @brief get_last_non_whitespace searches for last non whitespace character in string
     * @param s string
     * @return  last non whitespace character
     */
    static char get_last_non_whitespace(const std::string & s);

    /**
     * @brief get_block locates start and end position of text block
     * @param val string to search in
     * @param block_starter character that indicates block start
     * @param block_ender character that indicates block end
     * @param start_pos start position is saved in this reference
     * @param end_pos end position is saved in this reference
     * @param pos position which string is serched from
     */
    static void get_block(const std::string & val, char block_starter, char block_ender, size_t & start_pos, size_t & end_pos, size_t pos =0);
};

#endif // PARSER_H
