#include<match.h>
int regex::regex_check(const std::string& pattern){
  if(pattern.size()==0)return 0;
  else{
    if(pattern[0]=='*')return 0;
  }
  auto isunit = [](const char ch)->bool{
    return (ch>='a'&&ch<='z')||ch=='.'||ch=='*';
  };
  for(int i=0;i<pattern.size();++i){
    if(!isunit(pattern[i])){return i;}
    if(pattern[i]=='*'){
      if(i+1!=pattern.size()&&pattern[i+1]=='*'){return i+1;}
    }
  }return -1;
}
bool regex::match(const std::string&pat){
  int code;
  if((code=regex_check(pat))!=-1){
    if(pat.size()==0)throw std::string("empty pattern is not allowed");
    else throw pat+":repeat `*` or unacceptable char at ["+std::to_string(code)+"]";
    return false;
  } // notnull
  std::string_view pattern(pat),text(__text);
  // while(text.size()){
  //   if(match_start(text,pattern)){return true;}
  //   text = text.substr(1);
  // }
  do{
    if(match_start(text,pattern)){return true;}
    if(text.size()){text = text.substr(1);}
  }while(text.size());
  return false;
}
bool regex::match_start(std::string_view text,std::string_view pat){
  if(pat.size()==0)return true;
  if(pat.size()==1)return pat[0] == '.' || pat[0] == text[0];
  if(pat[1] == '*')return match_star(text,pat[0],pat.substr(2));
  if(text.size()!=0 && (pat[0] == '.' || pat[0] == text[0])){
    return match_start(text.substr(1),pat.substr(1));
  }return false;
}
bool regex::match_star(std::string_view text,const char ch,std::string_view pat){
  do{
    if(match_start(text,pat)){return true;}
    if(text.size()){text = text.substr(1);}
  }while(text.size());
  return false;
}
bool regex::re_match(std::string const&text,std::string const&pattern){
  return regex(text).match(pattern);
}