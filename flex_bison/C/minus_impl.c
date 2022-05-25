#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "minus.h"

#define PARSE_DEBUG 0

#pragma region ast
static const int PSize = sizeof(struct ast*);
#ifdef LEX
struct lex* newlex(const char*text){
  struct lex* val = malloc(sizeof(struct lex));
  val->val = strdup(text);
  val->len = strlen(text);
  return val;
}
struct ast* newterm(int type, struct lex* val) {
  if(val){
    char* token = val->val;
    free(val);
    val = NULL;
    return newast(type, 0, token);
  }else return NULL;
}
#else
struct ast* newterm(int type, const char* val) {
  // char* token = (char*)malloc(val->len+1);
  // strncpy(token,val->val,val->len);
  // token[val->len] = 0;
  return newast(type, 0, val);
}
#endif
struct ast* newast(int type,int cnt, const char* val, ...) {
  struct ast* node = (struct ast*)malloc(sizeof(struct ast) + cnt * PSize);
  if (node) {
    node->type = type;
    node->node_cnt = cnt;
    node->value = val;
    if(type>0){
      debugf("len:%d|val:%s\n",strlen(val),val);
    }
    debugf("malloc t:%d value:%s\t children:%d\n",type,val,cnt);
    /* load children */
    va_list ap;
    va_start(ap, val);
    for (int i = 0; i < cnt; ++i) {
      node->childen[i] = va_arg(ap, struct ast*);
      // if(node->childen[i]) printf("\tchild:%d val:<%s>\n",i,node->childen[i]->value);
    }
  } else {
    yyerror("out of memory");
  }
  return node;
}
static const char* indent = "  "; /* double blank */
void show_ast(struct ast* root, int it) {
  static unsigned seq = 0;
  if (root) {
    printf("%d. ",++seq);
    for (int i = 0; i < it; ++i) {
      printf("%s", indent);
    }
    printf("%s\n",root->value);
    // if(root->node_cnt){
    //   for (int i = 0; i < it; ++i) {
    //     printf("%s", indent);
    //   }
    //   printf("%s\n",root->value);
    // }
    for (int i = 0; i < root->node_cnt; ++i) {
      show_ast(root->childen[i], it + 1);
    }
  }
}
void eval_helper(struct ast* root, int cnt, eval_fn fn) {
  if (root) {
    fn(root, cnt);
    for (int i = 0; i < root->node_cnt; ++i) {
      fn(root->childen[i], cnt + 1);
    }
  }
}
void eval(struct ast* root, eval_fn fn) {
  if (root) {
    eval_helper(root, 1, fn);
  }
}
void astfree(struct ast* root) {
  if (root) {
    for (int i = 0; i < root->node_cnt; ++i) {
      astfree(root->childen[i]);
    }
    if(root->type>0) free(root->value);
    free(root);
    root = NULL;
  }
}
#pragma endregion
void yyerror(char* s, ...) {
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error:\033[31m", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\033[0m\n");
}
void debugf(const char*fmt,...){
  #if PARSE_DEBUG == 1
  va_list ap;
  va_start(ap,fmt);
  vfprintf(stdout,fmt,ap);
  #endif
}

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    if ((yyin = fopen(argv[i], "r"))) {
      if (yyparse()) {
        yyerror("parse error when process file:%s", argv[i]);
      }
    } else {
      yyerror("can't open file:%s", argv[i]);
    }
  }
}