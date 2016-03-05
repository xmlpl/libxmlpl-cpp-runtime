#ifndef CURLDATASOURCE_H
#define CURLDATASOURCE_H

#include <BasicUtils/BasicThread.h>

#include "DataSource.h"

#include <curl/curl.h>

#include <iostream>

namespace xmlpl {
  class CuRLDataSource : public DataSource, protected BasicThread {
    String url;
    CURL *curl;
    CURLcode errorCode;

    bool atEOF;

    BasicCondition dataCond;
    char *data;
    long size;

  public:
    CuRLDataSource(const String &url);
    virtual ~CuRLDataSource();
    
    int read(char *&buffer);
    bool eof();

    virtual void run();

  protected:
    void initCurl();
    void throwError(const std::string &msg);

    int dataAvailable(char *data, long size);

    static int writer(char *data, size_t size, size_t nmemb,
		      CuRLDataSource *source);
  };
};
#endif // CURLDATASOURCE_H
