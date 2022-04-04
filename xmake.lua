target("lexer") -- lexer lib
  set_kind("static")
  add_includedirs("include")
  add_files("src/token.cpp","src/lexer.cpp")
target_end()
target("minus-lexer") -- lexer
  set_kind("binary")
  add_includedirs("include")
  add_files("Lexer.cpp")
  add_deps("lexer")
target_end()

target("test")
  add_includedirs("include")
  add_files("src/*.cpp","test/main.cpp")
target_end()