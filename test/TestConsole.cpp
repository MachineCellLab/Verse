
#include <iostream>
#include "TokenMap.h"
#include "Console.h"

using namespace std;


/* example tokenizer function
*/
void TokenizeUserLine(const char* line, const size_t len,
                       Token& command, ArgsVector& argsVector) {

    command = "";
    argsVector.clear();


    if ((line) && (len)) {
        char* buf = new char[len];

        size_t k = 0; 
        size_t n = 0;

        bool loopy = true;

        Token nxt("");
        TokenList tknList;

        //std::cout << "TokenizerUserLine(): tokenizing " << line << endl;

        while (isspace(line[k]) && (k<len)) { k++; }; // skip initial whitespace

        //std::cout << "TokenizerUserLine(): initial whitespace skipped, ";
	//std::cout << "first letter is: " << line[k] << endl;

        while (loopy)
	  {
	  if ((line[k] == 0) ||
	      (line[k] == '\n') ||
	      (line[k] == '#'))
	    {
	      //std::cout << "Tknizer END OF LINE\n";

	      if (n > 0) // add whatever token we were composing
		{
		  buf[n] = 0;
		  nxt = buf;
		  tknList.push_back(nxt);
		  //std::cout << "TokenizerUserLine(): pushed last token: " << nxt << endl;
		}

	      loopy = false;
	    }
	  else if (isspace(line[k])) // end-of-token
	    { 
                buf[n] = 0;
                nxt = buf;
                tknList.push_back(nxt);
                n = 0; k++;

                //std::cout << "TokenizerUserLine(): pushed token: " << nxt << endl;
                nxt = "";
            }
            else { // nothing special, copy it.
	      //std::cout << "TokenizerUserLine(): copying char: " << line[k] << endl;
                buf[n++] = line[k++];
            }
        } // end loop

        // populate output args
        if (tknList.size() > 0)
	  {
	    command = tknList.front();
	    tknList.pop_front();

	    while (tknList.size() > 0) // any args to add?
	      { 
		argsVector.push_back(tknList.front());
                tknList.pop_front();
	      }
	  }

        // we're done here...
        tknList.clear();
        delete[] buf;
    }
}



void testTokenMap(void) {
  TokenMap<Token> testMap("<null-string>");

  string aKey("a");
  string bKey("b");
  string cKey("c");
  string badKey("d");

  string aItem("the letter A");
  string bItem("the letter B");
  string cItem("the letter C");
  
  testMap.setValue(aKey, aItem);
  testMap.setValue(bKey, bItem);
  testMap.setValue(cKey, cItem);

  cout << "a maps to: " << testMap.getValue(aKey) << "\n";
  cout << "b maps to: " << testMap.getValue(bKey) << "\n";
  cout << "c maps to: " << testMap.getValue(cKey) << "\n";


  cout << "d maps to: " << testMap.getValue(badKey) << "\n";

  testMap.unsetValue(bKey);
  cout << "b NOW maps to " << testMap.getValue(bKey) << "\n";

  testMap.clear();

  cout << "cleared testMap size is: " << testMap.size() << "\n";
}

/**/
typedef struct _testConsole {
  string name;
  int version;
} testConsole;


void InitConsole(testConsole& data) {
  data.name = "test console";
  data.version = 1;
}
  
/** callbacks **/

void Set_Callback(testConsole& con, const ArgsVector& argsVector) {
  if (argsVector.size() == 2) {
    if (argsVector[0] == "name") {
      con.name = argsVector[1];
    }
    else if (argsVector[0] == "version") {
      con.version = stoi(argsVector[1]);
    }
    else {
      std::cout << "usage: set (name | version)\n";
    }
  }
  else {
    std::cout << "usage: set (name | version)\n";
  }
}

void Print_Callback(testConsole& con, const ArgsVector& argsVector) {
  if (argsVector.size() == 1) {
    if (argsVector[0] == "name") {
      std::cout << con.name << endl;
    }
    else if (argsVector[0] == "version") {
      std::cout << con.version << endl;
    }
    else {
      std::cout << "usage: print (name | version)\n";
    }
  }
  else {
    std::cout << "usage: print (name | version)\n";
  }
}

void Exit_Callback(testConsole& con, const ArgsVector& argsVector) {
    //con.Exit();
  std:: cout << "Exiting.\n";
  exit(0);
}

/*
    our toy syntax for this console test is:

    set name <new-name> #sets the name

    set version <new-version> #sets the version

    print name

    print version

    exit
*/

/**/
void testConsoleInstance(void) {
  Console<testConsole> TestConsole(InitConsole);

  cout << "Console name set to: " << TestConsole.PeekData().name << endl;
  cout << "Console version set to: " << TestConsole.PeekData().version << endl;

  string xk = "x";
  string xv = "3";
  
  TestConsole.Vars.setValue(xk, xv);

  cout << "hasValue returns: " << TestConsole.Vars.hasValue(xk) << endl;
  cout << "getValue returns: " << TestConsole.Vars.getValue(xk) << endl;

  TestConsole.Vars.unsetValue(xk);

  cout << "hasValue returns: " << TestConsole.Vars.hasValue(xk) << endl;
  cout << "getValue returns: " << TestConsole.Vars.getValue(xk) << endl;

}

/**/
void runConsoleInstance(void) {
    Console<testConsole> TestConsole(InitConsole);

    /* attach the callbacks & kick it off...
    */
    TestConsole.AddCallbackEntry("set",   Set_Callback, "set name or version", "set (name | version) <value>", 2, 2);
    TestConsole.AddCallbackEntry("print", Print_Callback, "print name or version", "print (name | version)", 1, 1);
    TestConsole.AddCallbackEntry("exit",  Exit_Callback, "exit this featureful computer program...", "exit [status]", 0, 1);

    TestConsole.User.SetTokenizerFunction(TokenizeUserLine);

    TestConsole.User.SetPrompt("READY:> ");
    TestConsole.Run();
}

/**/
int main (int argc, char* argv[]) {
  int rtn = 0;
  
  // testTokenMap();

  // testConsoleInstance();

  runConsoleInstance();

  return rtn;
}
