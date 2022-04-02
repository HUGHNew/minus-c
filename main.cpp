#include<iostream>
#include"lexer.h"
int main(){
  Lexer l(true);
  l.load_code(R"(/* A program to perform Euclid's
Algorithm to compute gcd. */

int gcd (int u, int v)
{
    if (v == 0)
        return u ;
    else
        return gcd(v,u-u/v*v);
    /* u-u/v*v ==
    u mod v */
}

void main(void)
{
    int x; int y;
    x = input();
    y = input();
    output(gcd(x,y));
})");
  try{
    l.execute(true);
  }catch(std::runtime_error const&re){
    std::cerr<<re.what()<<std::endl;
  }
  return 0;
}