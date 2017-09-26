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
std::string HTTP::sendRequest(int method, LPCSTR host, LPCSTR url, LPCSTR header, LPCSTR data)
{
    char httpUserAgent[512];
    DWORD szhttpUserAgent = sizeof(httpUseragent);
    ObtainUserAgentString(0, httpUseragent, &szhttpUserAgent);

    char m[5];
    if(method == GET)
  		strcpy(m, "GET");
  	else
  		strcpy(m, "POST");

    HINTERNET internet = InternetOpenA(httpUseragent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if(internet == NULL)
    {
      InternetCloseHandle(internet);
      return NULL;
    }

    HINTERNET connect = InternetConnectA(internet, host, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if(connect == NULL)
    {
      InternetCloseHandle(connect);
      return NULL;
    }

    HINTERNET request = HttpOpenRequestA(connect, m, url, "HTTP/1.1", NULL, NULL, INTERNET_FLAG_HYPERLINK | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID | INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP  | INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_NO_UI | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, NULL);

    if(request == NULL)
      return NULL;

    int datalen = 0;
    if(data != NULL)
      datalen = strlen(data);
    int headerlen = 0;
    if(header != NULL)
      headerlen = strlen(header);

    	HttpSendRequestA(request, header, headerlen, data, datalen);
      InternetCloseHandle(request);
}
#endif
