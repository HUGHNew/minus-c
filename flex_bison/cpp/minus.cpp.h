#include <memory>
#include <string>
#include <vector>

#pragma once

class AstNode;
using pointer = std::shared_ptr<AstNode>;

class AstNode {
  int type;
  std::string name;
  std::vector<pointer> children;

 public:
  AstNode(int _t, std::string const& n) : type(_t), name(n) {}
  AstNode(int _t, std::string const& n,
          std::initializer_list<pointer> const& cs)
      : type(_t), name(n), children(cs) {}
  static pointer create(int _t, std::string const& n) {
    return std::make_shared<AstNode>(_t, n);
  }
  static pointer create(int _t, std::string const& n,
                        std::initializer_list<pointer> const& cs) {
    return std::make_shared<AstNode>(_t, n, cs);
  }
};
void show_ast(pointer const& p) noexcept;