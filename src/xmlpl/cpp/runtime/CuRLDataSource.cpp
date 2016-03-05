#include "CuRLDataSource.h"

#include <string>

using namespace std;
using namespace xmlpl;


CuRLDataSource::CuRLDataSource(const String &url) :
  DataSource(url), url(url), curl(0), atEOF(false), data(0), size(0) {
}

CuRLDataSource::~CuRLDataSource() {
}

int CuRLDataSource::read(char *&buffer) {
  if (atEOF) return 0;
  if (!curl) initCurl();

  signal(); // Signal room
  wait();   // Wait for data

  buffer = data;
  return size;
}

bool CuRLDataSource::eof() {
  return atEOF;
}

void CuRLDataSource::run() {
  lock();

  errorCode = curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  data = 0;
  size = 0;

  atEOF = true;
  broadcast();
  unlock();
}

void CuRLDataSource::initCurl() {
  curl = curl_easy_init();
  if (!curl) throwError("Failed to create connection");  

  if (curl_easy_setopt(curl, CURLOPT_URL, url.cstr()) != CURLE_OK)
    throwError("Setting url");

  if (curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1) != CURLE_OK)
    throwError("Setting CURLOPT_FOLLOWLOCATION");

  if (curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer) != CURLE_OK)
    throwError("Setting CuRL writer function");

  if (curl_easy_setopt(curl, CURLOPT_WRITEDATA, this) != CURLE_OK)
    throwError("Setting CuRL writer function data"); 

  // Start the read thread
  lock();
  start();
}

void CuRLDataSource::throwError(const string &msg) {
  throw BasicException(string("URL = '") + url.cpp_str() + "' " + msg);
}

int CuRLDataSource::dataAvailable(char *data, long size) {
  this->data = data;
  this->size = size;

  signal(); // Signal data
  wait();   // Wait for room

  return size;
}

int CuRLDataSource::writer(char *data, size_t size, size_t nmemb,
			   CuRLDataSource *source) {
  return source->dataAvailable(data, size * nmemb);
}
