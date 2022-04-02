#include<string>
#include<fstream>
#include<vector>
#include"token.h"

#pragma once

class Lexer{
  using str=std::string;
  str source;
  bool debug_mode;
  size_t row,col;
  size_t sb,mb,bb; // () [] {} the count of diff brakets
  std::vector<Token> tokens;
  /**
   * @brief skip the comment
   * @param slash start position of left slash
   * @return the length of comment (the offset)
   * @exception runtime_error if occurs an open comment
  */
  size_t skip_comment(size_t slash);
  bool isbraket(char ch,bool process=true);
  void reset();
  inline Token get_token(str const&,Type);
  inline void push_token(const Token&);
  inline void push_token(str const&,Type);
public:
  Lexer(bool debug=false):row(1),col(1),sb(0),mb(0),bb(0),debug_mode(debug){}
  Lexer& load_file(const str&file);
  Lexer& load_code(const str&code);
  std::vector<Token> execute(bool debug=false);
  # pragma region token getter
  /**
   * @brief the same funtion as @skip_comment
   * @return offset
  */
  size_t getId(size_t start);
  size_t getOp(size_t start);
  size_t getNum(size_t start);
  # pragma endregion
  inline static str gen_err_msg(size_t row,size_t col,str const&msg){
    return "Line: "+std::to_string(row)+
            " Col: "+std::to_string(col)+
            "\terror msg:"+msg;
  }
  inline str gen_err_msg(str const&msg){return gen_err_msg(row,col,msg);}
};