#include "HTTP.h"
#ifdef __APPLE__
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
#endif

#ifdef _WIN32

std::string HTTP::sendRequest(LPCSTR method, LPCSTR host, LPCSTR url, LPCSTR header, LPCSTR data)
{
  std::string response;
  HINTERNET hInternet = InternetOpen(TEXT("httpRequest"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
  HINTERNET session = InternetConnect(hInternet, host, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
  HINTERNET request = HttpOpenRequest(session, method, url, "HTTP/1.1", NULL, NULL, INTERNET_FLAG_HYPERLINK, NULL);

  int datalen = 0;
  if(data != NULL)
    datalen = strlen(data);

  int headerlen = 0;
  if(header != NULL)
    headerlen = strlen(header);

  BOOL res = HttpSendRequest(request, header, headerlen, (char*)data, datalen);

  if(res)
  {
    const int buffSize = 1024;
    char buff[buffSize];

    bool read = true;
    DWORD bytesRead = -1;
    while(read && bytesRead != 0)
    {
      read = InternetReadFile(request, buff, buffSize, &bytesRead);
      response.append(buff, bytesRead);
    }
  }

  InternetCloseHandle(request);
  InternetCloseHandle(session);
  InternetCloseHandle(hInternet);

  return response;
}
#endif
