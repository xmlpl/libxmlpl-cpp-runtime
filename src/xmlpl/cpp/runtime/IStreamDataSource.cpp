#include "IStreamDataSource.h"

using namespace std;
using namespace xmlpl;

IStreamDataSource::IStreamDataSource(std::istream &in, const String &name) :
  DataSource(name), in(in) {
}

IStreamDataSource::~IStreamDataSource() {
}

int IStreamDataSource::read(char *&buffer) {
  in.read(buf, bufferSize);
  buffer = buf;
  return in.gcount();
}

bool IStreamDataSource::eof() {
  return in.eof();
}
