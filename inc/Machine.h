/*

*/

#ifndef _machine_h_
#define _machine_h_

#include <cstring>

#include <string>
#include <list>
#include <map>
#include <vector>

using namespace std;

/* Boundary types... 
*/
typedef size_t Index;
typedef size_t Count;
typedef size_t Size;

typedef ssize_t Integer;

typedef double Real;

typedef string Text;

/* internal Token types
*/
typedef std::string Token;

typedef std::list<Token> TokenList;

typedef std::vector<Token> ArgsVector;

#endif

