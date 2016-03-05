#include "Functions.h"

using namespace std;
using namespace xmlpl;

namespace xmlpl {
  vector<string> tokenize(const string &str, const string &delimiters) {
    vector<string> tokens;
  
    // skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    
    // find first "non-delimiter".
    string::size_type pos = str.find_first_of(delimiters, lastPos);
    
    while (string::npos != pos || string::npos != lastPos) {
    // found a token, add it to the vector.
      tokens.push_back(str.substr(lastPos, pos - lastPos));
      
      // skip delimiters.  Note the "not_of"
      lastPos = str.find_first_not_of(delimiters, pos);
      
      // find next "non-delimiter"
      pos = str.find_first_of(delimiters, lastPos);
    }
    
    return tokens;
  }
};
