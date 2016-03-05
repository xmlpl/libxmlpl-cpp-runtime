#include "Version.h"

#include <xmlpl/cpp/runtime/Functions.h>

#include <BasicUtils/BasicString.h>

#include <vector>
#include <stdlib.h>

using namespace std;
using namespace xmlpl;

Version::Version(const std::string version) : _major(0), _minor(0), _revision(0) {
  vector<string> parts = tokenize(version, ".");
  
  if (parts.size() > 0) _major = atoi(parts[0].c_str());
  if (parts.size() > 1) _minor = atoi(parts[1].c_str());
  if (parts.size() > 2) _revision = atoi(parts[2].c_str());
}

string Version::toString() const {
  return BasicString(_major) + "." + BasicString(_minor) + "." + BasicString(_revision);
}
