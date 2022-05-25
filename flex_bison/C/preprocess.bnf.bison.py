from typing import List

head = ""
def judge_type(line:str)->int:
  """
  0 - first line
  1 - | line
  2 - ; line
  """
  if line[0].isalpha():
    return 0
  else: return 1 if '|' in line else 2
def wrap_lexeme(lex:str,idx:int)->str:
  t = "Sign"
  if "op" in lex:
    t = "Op"
  if lex == "ID":
    t = "Id"
  if lex.isupper() or "op" in lex:
      return f"newterm({t},${idx})"
  else: return f"${idx}"
def add_rule(pat:str,parts:list)->str:
  return f"{{$$=newast(NoT,{len(parts)},\"{pat.lower()}\",{','.join([wrap_lexeme(lex,i+1) for i,lex in enumerate(parts)])});}}"
def modify(s:str)->str:
  _t = judge_type(s)
  global head
  if _t == 1:
    st = s.find('|')
    last = s[st+1:-1]
    pat = head+"->"+last
    return s[:-1]+add_rule(pat,[p.strip() for p in last.split(' ') if p.strip()!=''])
  elif _t == 0:
    head = s[:s.find(' ')]
    pat = s.replace(':',"->")[:-1]
    pat = pat.replace(":|",':')
    st = s.find(':')
    return s[:-1]+add_rule(pat,[p.strip() for p in s[st+1:-1].split(' ') if p.strip()!=''])
  return s
def add_actions(filename:str)->List[str]:
  with open(filename,mode="r") as fd:
    content = fd.readlines()
  # _t = judge_type()
  content = [modify(line) for line in content]
  return content
table = {
  " semi":" ;",
  " comma":" ,",
  " ll":" {",
  " rl":" }",
  " lm":" [",
  " rm":" ]",
  " ls":" (",
  " rs":" )",
  " ass":" =",
  "->|":"-> empty|",
  ":|":":{$$=NULL;}|"
}
def post_wrap(l:str)->str:
  for k,v in table.items():
    l=l.replace(k,v)
  return l
def post_pro(l:List[str])->List[str]:
  return [post_wrap(line) for line in l]
if __name__ == "__main__":
  # todo
  [print(line) for line in post_pro(add_actions("minus.bison.bnf"))]