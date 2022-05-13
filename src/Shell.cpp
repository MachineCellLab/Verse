

#include "Shell.h"

Shell::Shell() {

}

Shell::~Shell() {

}


void Shell::Session(void) {
  string bashCmd = "bash";
  Exec(bashCmd); // will return upon bash exit();
}

void Shell::Exec(const string& commandLine) {

}

void Shell::Exec(Token& command, ArgsVector& args) {

}

void Shell::Spawn(const string& commandLine) {

}

void Shell::Spawn(Token& command, ArgsVector& args) {
  
}
  

bool Shell::Variable(const Token& name, Token& value) {
  bool tf = false;
  
#ifdef _GNU_SOURCE
  char *varChar = secure_getenv(name.c_str());
#else
  char *varChar = getenv(name.c_str());
#endif

  if (varChar) {
    value = varChar;
    tf = true;
  }
  
  return tf;
}
