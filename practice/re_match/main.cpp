#include<iostream>
#include<vector>

#include<match.h>
#include<debug.hpp>

// re_match("gooood", "go*d");
// re_match("key", "keys*");
// [.] re_match("scu-cs", "scu.cs");
// [.] re_match("compilable", ".*able");
int main(){
  std::vector<std::string> 
    texts{"goood","goood","scu-cs","compilable","","","key"},
    regex{"go*d","g.*od","scu.cs*",".*able",".*able",".*a*b*",""};
  try{
    for(int i = 0 ;i<texts.size();++i){
      Debug::assert(regex::re_match(texts[i],regex[i]),[&](){
        std::cerr<<'\''<<texts[i]<<"\' not match '"<<regex[i]<<'\''<<std::endl;
      });
    }
  }catch(const char*e){
    std::cout<<e<<std::endl;
  }catch(std::string const&s){
    std::cerr<<s<<std::endl;
  }
  return 0;
}