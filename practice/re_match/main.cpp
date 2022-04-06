#include<iostream>
#include<vector>
#include<map>

#include<match.h>
#include<debug.hpp>

// re_match("gooood", "go*d");
// re_match("key", "keys*");
// [.] re_match("scu-cs", "scu.cs");
// [.] re_match("compilable", ".*able");
int main(){
  std::map<std::string,std::string> examples{
    {"goood","go*d"},
    {"gooood","g.*d"},
    {"scu-cs","scu.cs*"},
    {"compilable",".*able"},
    {"",".*a*b*"},
    {"key","keys*"},
    {"abc","efg"},
    {"abcd","**"}
  };
  for(auto &&it:examples){
    try{
      Debug::assert(regex::re_match(it.first,it.second),[&](){
        std::cerr<<"\'"<<it.first<<"\' not match '"<<it.second<<'\''<<std::endl;
      });
    }catch(std::string const&s){
      std::cerr<<"\'"<<it.first<<"\' not match '"<<it.second<<'\''<<std::endl;
    }catch(...){std::cout<<"???"<<std::endl;}
  }
  return 0;
}