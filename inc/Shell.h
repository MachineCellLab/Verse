


#ifndef _console_shell_h_
#define _console_shell_h_

#include "TokenMap.h"

using namespace std;

class Shell {
 private:

 protected:

 public:
  Shell();

  ~Shell();

  /*
    getenv()
    execvp()
    system()
    execcl()
   */

  void Session(void); ///< Run a local sub-shell.

  void Exec(const string& commandLine); ///< shell-exec this command line.
  void Exec(Token& command, ArgsVector& args); ///< shell-exec this command line.

  void Spawn(const string& commandLine); ///< shell-exec this command line, sep process..
  void Spawn(Token& command, ArgsVector& args); ///< shell-exec this command line, sep process...
  
  bool Variable(const Token& name, Token& value); ///< obtain value of environment variable
};

#endif // _console_shell_h_
