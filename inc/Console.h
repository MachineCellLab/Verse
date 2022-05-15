
#ifndef _console_src_h_
#define _console_src_h_

#include <cstring>
#include <iostream>

#include "TokenMap.h"
#include "LineReader.h"
#include "Shell.h"

template <class T>
class Console {
 private:
  bool isRunning;

 public:
  typedef void(*CmdCallback)(T& data, const ArgsVector& argsVector);

  typedef void(*DataCallback)(T& data);

  typedef void(*DataArgCallback)(T& data, void* arg);

  typedef void(*PeekCallback)(const T& data);
  
 protected:
  T data;
  
 public:
  /**
    @par Vars & Cmds: 
    These are both TokenMaps, one string:string, the other string::CmdCallback. Rather than
    write Console-level methods to wrap add/get/etc, we just expose these as 'public'
    so they can be called directly.
   */
  TokenMap<Token> Vars; ///< Variables (string::string map)

  TokenMap<CmdCallback> Cmds; ///< Commands (string::callback map)

  LineReader User; ///< User Text interface (linenoise implementation).

  Shell Env; ///< Interface to local shell (posix)

  /*
    Methods
   */
  T& Data(void){ return (T&)data; }; ///< access Console Data

  const T& PeekData(void){ return (const T&)data; }; ///< access Console Data (read only)

  void DispatchCmd(const Token& cmd, const ArgsVector& argsVector) { ///< Dispatch user command
    if (CmdCallback cbk = Cmds.getValue(cmd)) {
	    cbk(data, argsVector);
      }
    else {
        std::cout << "CONSOLE:: INVALID COMMAND: " << cmd << endl;
    }
  };

 Console() : Vars("<null-variable>"), Cmds(NULL), isRunning(false){ }; ///< base constructor

 Console(DataCallback initCallback) : Vars("<null-variable>"), Cmds(NULL), isRunning(false)
    { ///< callback constructor
      if (initCallback) { initCallback(data); }
    };
  
  ~Console(){}; ///< Base destructor

  // runloop...

  void Exit(void) { ///< Exit the Console.
      isRunning = false;
  };

  void Run(void) { ///< Begin Console run-loop.
    isRunning = true;
    
    while (isRunning) {
      Token command = "";
      Token rawline = "";
      
      ArgsVector argsvector; argsvector.clear();
        
      User.GetTokenizedLine(command, argsvector);
      /*
      std::cout << "command is: " << command << endl;
      
      for (int k = 0; k < argsvector.size(); k++) {
	            std::cout << "argv[" << k <<"] is: " << argsvector[k] << endl;
      }*/
      
      DispatchCmd(command, argsvector);
    }
  };
};

#endif //_console_src_h_
