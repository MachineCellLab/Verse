

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
    
    tokenizerFunction(userLine.c_str(), userLine.size(),
		                command, argsVector);
  }
}

/* example tokenizer function 
*/
void TokenizeUserLine(const char* line, const size_t len,
		               Token& command, ArgsVector& argsVector) {

  command = "";
  argsVector.clear();

  if ((line) && (len)) {
    char* buf = new char[len];
    size_t k, n = 0;
    bool loopy = true;
    Token nxt("");
    TokenList tknList;

    while (isspace(line[k++])); // skip initial whitespace
    
    while (loopy) {
      if ((line[k] != 0) &&       // end of line?
	  (line[k] != '\n') &&
	  (line[k] != '#')) {
	buf[n]  = 0;              // yes, finsh
	nxt = buf;
	tknList.push_back(nxt);
	loopy = false;
      }
      else if (isspace(line[k])) { // end-of-token
	buf[n] = 0;
	nxt = buf;
	tknList.push_back(nxt);
	n = 0;
      }
      else { // nothing special, copy it.
	buf[n++] = line[k++];
      }
    } // end loop

    // populate output args
    if (tknList.size() > 0) {
      command = tknList.front();
      tknList.pop_front();
      
      while (tknList.size() > 0) { // any args to add?
	argsVector.push_back(tknList.front());
	tknList.pop_front();
      }
    }
      
    // we're done here...
    tknList.clear();
    delete[] buf;
  }
}



  // change toLower, if desired...

  // whitespace-delimited tokenize
  //   --1st token is 'command'
  //   --(n>1)th token added to argsVector

  // free raw user line

