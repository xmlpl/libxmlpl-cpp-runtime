#ifndef VERSION_H
#define VERSION_H

#include <string>

namespace xmlpl {
  class Version {
    unsigned int _major;
    unsigned int _minor;
    unsigned int _revision;
    
  public:
    Version() : _major(0), _minor(0), _revision(0) {}
    Version(const std::string version);
    Version(const unsigned int major, const unsigned int minor, const unsigned int revision) :
      _major(major), _minor(minor), _revision(revision) {}
    Version(const Version &v) : _major(v._major), _minor(v._minor), _revision(v._revision) {}
    
    unsigned int getMajor() const {return _major;}
    unsigned int getMinor() const {return _minor;}
    unsigned int getRevision() const {return _revision;}

    std::string toString() const;
    int compare(const Version &v) const {
      if (_major < v._major) return -1;
      if (_major > v._major) return 1;
      if (_minor < v._minor) return -1;
      if (_minor > v._minor) return 1;
      if (_revision < v._revision) return -1;
      if (_revision > v._revision) return 1;
      return 0;
    }

    bool operator==(const Version &v) const {
      return compare(v) == 0;
    }
    bool operator!=(const Version &v) const {
      return compare(v) != 0;
    }
    bool operator<(const Version &v) const {
      return compare(v) < 0;
    }
    bool operator<=(const Version &v) const {
      return compare(v) <= 0;
    }
    bool operator>(const Version &v) const {
      return compare(v) > 0;
    }
    bool operator>=(const Version &v) const {
      return compare(v) >= 0;
    }
  };
};
#endif // VERSION_H
