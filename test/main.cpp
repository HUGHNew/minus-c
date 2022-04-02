#include"lexer.h"
int main(){
  Lexer l(true);
  l.load_file("gcd.cminus");
  l.execute(true);
  return 0;
}