

#include "LineReader.h"

#include "linenoise.h"

LineReader::LineReader() : prompt("READY:> "), tokenizerFunction(0){
  
}


LineReader::~LineReader(){
  // linenoiseClearScreen();
}


void LineReader::Clear(void) {
  linenoiseClearScreen();
}

void LineReader::SetPrompt(const string& newPrompt) {
  prompt = newPrompt;
}

void LineReader::SetPrompt(const char* newPrompt) {
  prompt = newPrompt;
}

void LineReader::SetTokenizerFunction(TokenizerFunction tkfn) {
  tokenizerFunction = tkfn;
}

void LineReader::GetRawLine(string& line) {
  char* noiseline = linenoise(prompt.c_str());
  line = noiseline;
  linenoiseFree(noiseline);

  std::cout << prompt.c_str() << endl;
}

void LineReader::GetRawLine(char* line, size_t maxLineSize) {
  char* noiseline = linenoise(prompt.c_str());
  int k;

  while ((line[k] != '\n') &&
	 (line[k] != 0) &&
	 (k < maxLineSize)) {
    line[k] = noiseline[k++];
  }

  linenoiseFree(noiseline);
}

void LineReader::GetSecretLine(string& line) {
  // set mask
  // get a rawline
  // unset mask
}

void LineReader::GetTokenizedLine(Token& command, ArgsVector& argsVector) {
  if (tokenizerFunction) {
    string userLine = "";
    GetRawLine(userLine);
    
    if (tokenizerFunction) {
        tokenizerFunction(userLine.c_str(), 
                          userLine.size(),
                          command, 
                          argsVector);
    }
  }
}


