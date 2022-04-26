target("lexer") -- lexer lib
  set_kind("static")
  set_targetdir("lib")
  add_includedirs("include")
  add_files("src/token.cpp","src/lexer.cpp")
target_end()
target("minus-lexer") -- lexer
  set_kind("binary")
  set_targetdir("bin")
  add_includedirs("include")
  add_files("Lexer.cpp")
  add_deps("lexer")
target_end()
target("minus-preprocessor") -- preprocess
  set_kind("binary")
  set_targetdir("bin")
  add_files("Preprocessor.cpp","src/preprocessor.cpp")
target_end()

includes("practice/re_match")