
#include <iostream>
#include "TokenMap.h"
#include "Console.h"

using namespace std;

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
  
  testTokenMap();

  testConsoleInstance();

  return rtn;
}
