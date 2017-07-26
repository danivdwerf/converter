#include "HTTP.h"
std::string HTTP::sendRequest(std::string url, std::map<std::string, std::string> headers, std::string values)
{
  Poco::URI uri(url);
  std::string path(uri.getPathAndQuery());
  if (path.empty()) path = "/";

  Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
  Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);

  request.setContentType("application/x-www-form-urlencoded");

  for(std::map<std::string, std::string>::iterator i = headers.begin(); i != headers.end(); i++)
    request.set(i->first, i->second);
  request.setContentLength(values.length());

  std::ostream& os = session.sendRequest(request);
  os<<values;

  Poco::Net::HTTPResponse response;
  std::istream& is = session.receiveResponse(response);

  std::stringstream ss;
  Poco::StreamCopier::copyStream(is, ss);
  return ss.str();
}
