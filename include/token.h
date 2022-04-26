#include<string>
#include<unordered_map>
#include<set>
#include<stdexcept>

#pragma once

enum class Type:short{
  id,keyword,number,op,error
};

struct Token{
  using str=std::string;
  Type type;
  str name;
  size_t line,col;
  Token(const str&source,Type _t,size_t lc,size_t cc)
      :name(source),type(_t),line(lc),col(cc){}
  str to_string(bool detail=false)const noexcept;
  bool is_keyword(bool modify=true);
  static char next_op(char ch){
    static std::unordered_map<char,char> op_table{
      {'<','='},{'>','='},{'=','='},{'!','='}
    };
    try{
      return op_table.at(ch);
    }catch(const std::out_of_range&){return 0;}
  }
  static bool invalid_op(char ch){
    static std::set<char> invalid_singles{'!'};
    return invalid_singles.count(ch);
  }
  static Type token_type(char ch){
    static std::set<char> valid_ops{
      '<','>','*','=','+','-','/',';',',',
      '(',')','[',']','{','}'
    };
    /**
     * id::= [a-zA-Z]+
     * num::= [0-9]+
     * sop::= [+-/*<>=;,()[]{}]
     * dop::= <=|>=|==|!=|/* /
    */
    if(isalpha(ch)!=0){return Type::id;}
    else if(ch>='0'&&ch<='9'){return Type::number;}
    else if(valid_ops.count(ch)){return Type::op;}
    else return Type::error;
  }
};