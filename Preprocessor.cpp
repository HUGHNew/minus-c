#include<iostream>
#include<string>
bool preprocess(const std::string&,std::string&);

int main(int argc,char* argv[]){
  std::string error;
  for(int i=1;i<argc;++i){
    if(!preprocess(argv[i],error)){
      std::cerr<<argv[i]<<": preprocessing error|msg:\033[31m"<<error<<"\033[0m"<<std::endl;
      return 1;
    }
  }
  return 0;
}