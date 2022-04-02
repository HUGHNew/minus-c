#include "lexer.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#pragma region private functions
size_t Lexer::skip_comment(size_t slash) {
  size_t sr = row, sc = col;  // start position
  for (size_t star = slash + 2; star < source.size(); ++star) {
    if (source[star] == '*' && star + 1 < source.size() &&
        source[star + 1] == '/') {
      col += 2;
      return star + 2 - slash;
      // return offset
    } else {
      if(source[star]=='\n'){
        ++row;col=1;
      }else ++col;
    }
  }
  throw std::runtime_error(
      gen_err_msg(sr, sc, "the start position of an open comment"));
}
void Lexer::reset() {
  row = col = 1;
  tokens.clear();
}
void braket_helper(char left, char right, char ch, size_t& val,
                   std::string const& err_msg) {
  if (ch == left) {
    ++val;
  } else if (ch == right) {
    if (val > 0) {
      --val;
    } else {
      throw std::runtime_error(err_msg);
    }
  }
}
bool Lexer::isbraket(char ch, bool process) {
  static std::string brakets("()[]{}");
  std::string err = gen_err_msg("invalid enclose braket here");
  if (brakets.find(ch) == std::string::npos) {
    return false;
  } else if (process) {
    braket_helper('(', ')', ch, sb, err);
    braket_helper('[', ']', ch, mb, err);
    braket_helper('{', '}', ch, bb, err);
    // add token
    push_token(str(1, ch), Type::op);
  }
  return true;
}
inline Token Lexer::get_token(str const& val, Type _t) {
  return Token(val, _t, row, col);
}
inline void Lexer::push_token(str const& val, Type _t) {
  push_token(Token(val, _t, row, col));
}
inline void Lexer::push_token(const Token& tk) {
  tokens.emplace_back(tk);
  if (debug_mode) {
    std::cout << tk.to_string(debug_mode) << std::endl;
  }
}
#pragma endregion
Lexer& Lexer::load_file(const std::string& file) {
  std::ifstream ifs(file);
  std::string temp;
  while (ifs) {
    std::getline(ifs, temp);
    source += temp;
  }
  if (debug_mode) {
    std::cout << "file content: " << source << std::endl;
  }
  this->reset();
  return *this;
}
Lexer& Lexer::load_code(const std::string& code) {
  source = code;
  if (debug_mode) {
    std::cout << "code: " << source << std::endl;
  }
  this->reset();
  return *this;
}
std::vector<Token> Lexer::execute(bool debug) {
  debug_mode = debug;
  if (tokens.size() != 0) return tokens;
  if (debug_mode) {
    std::cout << "begin to scan code" << std::endl;
  }
  for (size_t scan = 0; scan < source.size();) {
    if (isspace(source[scan])) {  // skip space
      if (source[scan] == '\n') {
        ++row;col = 1;
      } else { ++col; }
      ++scan; continue;  // end this pass
    }
    switch (Token::token_type(source[scan])) {
      case Type::id: {
        scan += getId(scan);
        break;
      }
      case Type::number: {
        scan += getNum(scan);
        break;
      }
      case Type::op: {
        scan += getOp(scan);
        break;
      }
      default: {  // error here
        // invalid char
        throw std::runtime_error(gen_err_msg(row, col, "invalid char"));
      }
    }
  }
  if(sb||mb||bb){
    throw std::runtime_error(gen_err_msg(row, col, "brakets not match"));
  }
  return tokens;
}

#pragma region token getter
size_t Lexer::getId(size_t start) {
  // end if op or space occur
  size_t eoi = source.size();
  for (size_t i = start; i < eoi; ++i) {
    if (!isalpha(source[i])) {  // end of id here
      if (isdigit(source[i])) {
        throw std::runtime_error(gen_err_msg("invalid identifier with number"));
      } else {
        eoi = i;
      }
    }
  }
  eoi -= start;
  Token tk{source.substr(start, eoi), Type::id, row, col};
  col += eoi;  // steps after push
  tk.is_keyword();
  push_token(tk);
  return eoi;
}
size_t Lexer::getOp(size_t start) {
  // process comment here
  size_t offset;
  if (source[start] == '/' && start + 1 < source.size() &&
      source[start + 1] == '*') {
    offset = skip_comment(start);
  } else if (isbraket(source[start])) {
    offset = 1;
  } else {  // other operators
    if (Token::next_op(source[start])) {
      push_token(source.substr(start, 2), Type::op);
      offset = 2;
    } else {
      if (Token::invalid_op(source[start])) {
        throw std::runtime_error(gen_err_msg("invalid operator"));
      }
      push_token(str(1, source[start]), Type::op);
      offset = 1;
    }
  }
  col += offset;
  return offset;
}
size_t Lexer::getNum(size_t start) {
  size_t eoi = source.size();
  for (size_t i = start; i < eoi; ++i) {
    if (!isdigit(source[i])) {
      if (isalpha(source[i])) {
        throw std::runtime_error(gen_err_msg("invalid number with char"));
      } else {
        eoi = i;
      }
    }
  }
  eoi -= start;
  Token tk{source.substr(start, eoi), Type::number, row, col};
  col += eoi;
  push_token(tk);
  return eoi;
}
#pragma endregion