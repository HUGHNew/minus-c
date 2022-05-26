#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "minus.h"

#define PARSE_DEBUG 0

#pragma region ast
#pragma region new
static const int PSize = sizeof(struct ast*);
#if LEX == 1
struct lex* newlex(const char* text) {
  struct lex* val = malloc(sizeof(struct lex));
  val->val = strdup(text);
  val->len = strlen(text);
  return val;
}
struct ast* newterm(int type, struct lex* val) {
  if (val) {
    char* token = val->val;
    free(val);
    val = NULL;
    return newast(type, 0, token);
  } else
    return NULL;
}
#else
struct ast* newterm(int type, const char* val) {
  return newast(type, 0, val);
}
#endif
struct ast* newast(int type, int cnt, const char* val, ...) {
  struct ast* node = (struct ast*)malloc(sizeof(struct ast) + cnt * PSize);
  if (node != NULL) {
    node->type = type;
    node->node_cnt = cnt;
    node->value = val;
    if (type > 0) {
      debugf("len:%d|val:%s\n", strlen(val), val);
    }
    debugf("malloc t:%d value:%s\t children:%d\n", type, val, cnt);
    /* load children */
    va_list ap;
    va_start(ap, val);
    for (int i = 0; i < cnt; ++i) {
      node->childen[i] = va_arg(ap, struct ast*);
      // if(node->childen[i]) printf("\tchild:%d
      // val:<%s>\n",i,node->childen[i]->value);
    }
  } else {
    yyerror("out of memory");
  }
  return node;
}
#pragma endregion
static const char* indent = "  "; /* double blank */
void Indent(FILE* fd, int count) {
  for (int i = 0; i < count; ++i) {
    fprintf(fd, "%s", indent);
  }
}
static unsigned seq = 0;
void show_ast_helper(struct ast* root, int it) {
  if (root != NULL) {
    // printf("%d. ", ++seq);
    int t_sum = 0;
    for (int i = 0; i < root->node_cnt; ++i) {
      if (root->childen[i]) {
        t_sum += root->childen[i]->type;
      }
    }
#ifdef PARSE_RULE
    Indent(stdout, it);
#endif
    if (root->type) {
#ifndef PARSE_RULE
      Indent(stdout, it - 1);
#endif
      printf("%s\n", root->value);
    } else {
#ifdef PARSE_RULE
      printf("<%s>\n", root->value);
#endif
      int n = t_sum == 0 ? it : it + 1;
      for (int i = 0; i < root->node_cnt; ++i) {
        show_ast_helper(root->childen[i], n);
      }
    }
  }
}
void show_ast(struct ast* root) { show_ast_helper(root, 0); }
#pragma region eval
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
#pragma endregion
void astfree(struct ast* root) {
  if (root != NULL) {
    if (root->node_cnt) {
      for (int i = 0; i < root->node_cnt; ++i) {
        astfree(root->childen[i]);
      }
    } else {
      free((char*)root->value);
    }
    // free(root);
    root = NULL;
  }
}
#pragma endregion
void yyerror(char* s, ...) {
  va_list ap;
  va_start(ap, s);
  extern int column;
  extern char* yytext;
  fprintf(stderr, "%d,%d: \033[32mToken:<%s> error:\033[31m", yylineno, column,yytext);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\033[0m\n");
}
void debugf(const char* fmt, ...) {
#if PARSE_DEBUG == 1
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stdout, fmt, ap);
#endif
}

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    if ((yyin = fopen(argv[i], "r"))) {
      printf("file:%s\n", argv[i]);
      if (yyparse()) {
        yyerror("parse error when process file:%s", argv[i]);
      }
    } else {
      yyerror("can't open file:%s", argv[i]);
    }
  }
}