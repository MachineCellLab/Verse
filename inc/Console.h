
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

  typedef struct CmdCallbackEntry {
      Token cmd;
      string usage, description;
      uint8_t minArgs, maxArgs;
      CmdCallback callback;
  } CmdCallbackEntry;
  
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

  TokenMap<CmdCallbackEntry> Cmds; ///< Commands (string::callback-entry map)

  LineReader User; ///< User Text interface (linenoise implementation).

  Shell Env; ///< Interface to local shell (posix)

  /*
    Methods
   */
  T& Data(void){ return (T&)data; }; ///< access Console Data

  const T& PeekData(void){ return (const T&)data; }; ///< access Console Data (read only)

  void DispatchCmd(const Token& cmd, const ArgsVector& argsVector) { ///< Dispatch user command
      if (CmdCallbackEntry cbkEntry = Cmds.getValue(cmd)) {
          if ((argsVector.size() >= cbkEntry.minArgs) &&
              (argsVector.size() <= cbkEntry.maxArgs) && cbkEntry.cbk) {
              cbkEntry.cbk(data, argsVector);
          }
          else {
              std::cerr << cbkEntry.usage << endl;
          }
      }
      else {
          std::cerr << "CONSOLE:: INVALID COMMAND: " << cmd << endl;
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


  void AddCallbackEntry(const string& cmd, CmdCallback callback,
      const string& description, const string& usage,
      const uint8_t minArgs,
      const uint8_t maxArgs)
  {
      CmdCallbackEntry newEntry;

      newEntry.cmd = cmd;
      newEntry.usage = usage;
      newEntry.description = description;
      newEntry.minArgs = minArgs;
      newEntry.maxArgs = maxArgs;
      newEntry.callback = callback;

      this->Cmds.setValue(cmd, newEntry);
  };

  void Run(void) { ///< Begin Console run-loop.
    isRunning = true;
    
    while (isRunning) {
      Token command = "";
      Token rawline = "";
      ArgsVector argsvector; argsvector.clear();
        
      User.GetTokenizedLine(command, argsvector);
      
      DispatchCmd(command, argsvector);
    }
  };
};

#endif //_console_src_h_
