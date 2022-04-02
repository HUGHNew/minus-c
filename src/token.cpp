#include"token.h"

namespace values{
  using std::unordered_map;
  static unordered_map<Type,std::string> t2n={
    {Type::id,"id"},
    {Type::keyword,"keyword"},
    {Type::number,"number"},
    {Type::op,"operator"}
  };
  static unordered_map<std::string,Type> n2t={
    {"id",Type::id},
    {"keyword",Type::keyword},
    {"number",Type::number},
    {"operator",Type::op}
  };
  static std::set<std::string>keywords{
    "if","else","int","return","void","while"
  };
}

std::string Token::to_string(bool detail)const noexcept{
  if(detail){
    return "<'"+name+"',"+values::t2n[type]+
      ",("+std::to_string(line)+","+std::to_string(col)+")>";
  }
  return "<"+name+","+values::t2n[type]+">";
}
bool Token::is_keyword(bool modify){
  bool flag = type == Type::id && values::keywords.count(name);
  if(modify && flag){
    type = Type::keyword;
  }
  return flag;
}