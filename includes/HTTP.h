#ifndef HTTP_H
#define HTTP_H

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>

#include <sstream>
#include <string>
#include <map>

class HTTP
{
  public: std::string sendRequest(std::string, std::map<std::string, std::string>, std::string);
};
#endif
