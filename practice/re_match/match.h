#include<string>
#include<string_view>
#ifndef __REGEX_CLASS__
#define __REGEX_CLASS__ 1
class regex{
  std::string __text;
public:
  regex(const std::string&content):__text(content){}
  regex(const char*content):__text(content){}
  /**
   * @brief regex for [a-z.*]
   * @exception `std::string` if pattern error occurs
   * @param pattern [a-z\.\*]*
  */
  bool match(const std::string&pat);
  static bool re_match(std::string const&text,std::string const&pattern);
private:
  /**
   * @return the error position of @param pattern
   * return -1 if no error
  */
  static int regex_check(const std::string& pattern);
  /**
   * @brief match the whole string
  */
  static bool match_start(std::string_view text,std::string_view pat);
  /**
   * @brief match c*
   * @param text the text to match
   * @param ch the char `c`
   * @param pat the pattern after `*`
  */
  static bool match_star(std::string_view text,const char ch,std::string_view pat);
};
#endif