#include<iostream>

#include"lexer.h"
int main(int argc,char*argv[]){
  if(argc==1){
    std::cout<<"no input files"<<std::endl;
  }
  Lexer l;
  for(int i=1;i<argc;++i){
    try{
      l.load_file(argv[i]);
      std::cout<<argv[i]<<":"<<std::endl;
      l.execute(true);
      l.set_mode(false);
    }catch(const char*s){
      std::cerr<<"file: "<<argv[i]<<s<<std::endl;
    }catch(std::runtime_error const&re){
      std::cerr<<"in "<<argv[i]<<"\t"<<re.what()<<std::endl;
    }
  }
  return 0;
}