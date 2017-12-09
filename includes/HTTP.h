#ifndef HTTP_H
#define HTTP_H

#include <Windows.h>
#include <WinInet.h>

#include <sstream>
#include <string>

class HTTP
{
  public: std::string sendRequest(LPCSTR method, LPCSTR host, LPCSTR url, LPCSTR header, LPCSTR data)
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
};
#endif
