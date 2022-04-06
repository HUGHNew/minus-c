#include<functional>
#pragma once
class Debug{
public:
  static void assert(bool expr,std::function<void(void)>callback = abort){
    if(!expr){callback();}
  }
};