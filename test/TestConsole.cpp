
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
        size_t k, n = 0;
        bool loopy = true;
        Token nxt("");
        TokenList tknList;

        while (isspace(line[k++])); // skip initial whitespace

        while (loopy) {
            if ((line[k] != 0) &&       // end of line?
                (line[k] != '\n') &&
                (line[k] != '#')) {
                buf[n] = 0;              // yes, finsh
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
// Cmdcallback)(T& data, const ArgsVector& argsVector)

void SetName_Callback(testConsole& con, ArgsVector& argsVector) {
    con.name = argsVector[1];
}

void SetVersion_Callback(testConsole& con, ArgsVector& argsVector) {
    con.version = argsVector[1];
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
int main (int argc, char* argv[]) {
  int rtn = 0;
  
  // testTokenMap();

  // testConsoleInstance();

  return rtn;
}
