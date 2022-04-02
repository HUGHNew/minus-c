#include<iostream>

#include"lexer.h"
int main(int argc,char*argv[]){
  Lexer l;
  for(int i=1;i<argc;++i){
    try{
      l.load_file(argv[i]);
      l.execute(true);
    }catch(const char*s){
      std::cerr<<"file: "<<argv[i]<<s<<std::endl;
    }catch(std::runtime_error const&re){
      std::cerr<<re.what()<<std::endl;
    }
  }
  return 0;
}