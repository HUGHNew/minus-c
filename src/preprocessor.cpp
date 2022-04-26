#include <fstream>
#include <string>

void spacing(std::string& str, size_t beg, size_t end) {
  for (size_t i = beg; i < end; ++i) {
    str[i] = ' ';
  }
}

bool preprocess(const std::string& filename, std::string& msg) {
  std::ifstream src(filename);
  if (!src.good()) {
    msg = "file not exists";
    return false;
  }
  std::string cache((std::istreambuf_iterator<char>(src)),
                    std::istreambuf_iterator<char>());
  src.close();
  int start, end, col = 0, row = 0;
  int sc, sr;  // start point row/col
  bool flag = false;
  for (size_t i = 0; i < cache.size(); ++i) {
    if (cache[i] == '/') {
      if (i + 1 < cache.size() && cache[i + 1] == '*') {
        if (!flag) {
          flag = true;
          start = i++;  // step one
          sc = col;
          sr = row;
        }
      }
    } else if (cache[i] == '*') {
      if (i + 1 < cache.size() && cache[i + 1] == '/') {
        if (flag) {
          flag = false;
          end = ++i + 1;  // step one too
          spacing(cache, start, end);
        }
      }
    }
    if (cache[i] == '\n') {
      ++row;
      col = 1;
    } else {
      ++col;
    }
  }
  if (flag) {
    msg = "row:" + std::to_string(sr) + " col:" + std::to_string(sc) +
          "\t open comment";
    return false;
  } else {
    std::ofstream dst(filename);
    dst << cache;
    dst.close();
    return true;
  }
}