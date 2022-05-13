

#ifndef _console_tokenmap_h_
#define _console_tokenmap_h_

#include <string>
#include <list>
#include <map>
#include <vector>

typedef std::string Token;

typedef std::list<Token> TokenList;

typedef std::vector<Token> ArgsVector;

template <class T>
class TokenMap
{
 private:
  std::map<Token, T> mapping;

  T nullItem;
  
 protected:
    TokenMap();
    
 public:
   TokenMap(const T& nullItem) : nullItem(nullItem) {};

    ~TokenMap() { mapping.clear(); };

  /* 
     TokenMap is just a thin wrapper of std::map, so these
     methods are all inline
  */

  bool hasValue(const Token& tkn) { return (mapping.count(tkn) > 0); };
  
  void setValue(const Token& tkn, T& item) { mapping[tkn] = item; };

  void unsetValue(const Token& tkn) {
    if (hasValue(tkn)) {
      mapping.erase(tkn);
    }
  };
  
  const T& getValue(const Token& tkn) {
    if (hasValue(tkn)) {
	return mapping.at(tkn);
      }
    else {
      return nullItem;
    }
  };

  size_t size(void) { return mapping.size(); }

  void clear(void) { mapping.clear(); }
  
};

#endif /* _console_tokenmap_h_ */
