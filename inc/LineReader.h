

#ifndef _console_linereader_h_
#define _console_linereader_h_

#include "TokenMap.h"

using namespace std;

class LineReader {
 public:
  typedef void(*TokenizerFunction)(const char* line,
				   const size_t len,
				   Token& command,
				   ArgsVector& argsVector);
  LineReader();

  ~LineReader();

  void Clear(void);

  void SetPrompt(const string& newPrompt);

  void SetPrompt(const char* newPrompt);

  void GetRawLine(string& line);

  void GetRawLine(char* line, size_t maxLineSize);

  void GetSecretLine(string& line);

  void GetTokenizedLine(Token& command, ArgsVector& argsVector);

  void SetTokenizerFunction(TokenizerFunction tkfn);
  
 private:
  string     prompt;
  TokenizerFunction tokenizerFunction;
};

#endif //_console_linereader_h_
