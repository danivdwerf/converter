#ifndef HTTP_H
#define HTTP_H

#ifdef __APPLE__
  #include <Poco/Net/HTTPClientSession.h>
  #include <Poco/Net/HTTPRequest.h>
  #include <Poco/Net/HTTPResponse.h>
  #include <Poco/StreamCopier.h>
  #include <Poco/Path.h>
  #include <Poco/URI.h>
  #include <Poco/Exception.h>
#endif

#ifdef _WIN32
  #include <windows.h>
  #include <wininet.h>
#endif

#include <sstream>
#include <string>
#include <map>

class HTTP
{
  #ifdef __APPLE__
    public: std::string sendRequest(std::string, std::map<std::string, std::string>, std::string);
  #endif

  #ifdef _WIN32
    public: std::string sendRequest(int, LPCSTR, LPCSTR, LPCSTR, LPCSTR);
  #endif
};
#endif
