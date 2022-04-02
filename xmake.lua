target("minus-lexer") -- lexer
  set_kind("binary")
  add_includedirs("include")
  add_files("src/*.cpp","Lexer.cpp")
target_end()

target("test")
  add_includedirs("include")
  add_files("src/*.cpp","test/main.cpp")
target_end()