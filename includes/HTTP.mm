#ifndef HTTP_H
#define HTTP_H

#import "Cocoa/Cocoa.h"
class HTTP
{
  public: const char* sendRequest(const char* url, const char* data)
  {
    NSURL* nsurl = [NSURL URLWithString:[NSString stringWithUTF8String: url]];
    NSMutableURLRequest* request = [NSMutableURLRequest requestWithURL:nsurl cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:60.0];
    [request setHTTPMethod:@"POST"];

    NSString* body = [NSString stringWithUTF8String: data];
    [request setHTTPBody: [body dataUsingEncoding:NSUTF8StringEncoding]];

    NSURLResponse* response;
    NSError* error = nil;
    NSData *receivedData = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];

    if(error!=nil)
       return "";

    NSString* res = [[NSString alloc] initWithData:receivedData encoding:NSUTF8StringEncoding];
    return [res cStringUsingEncoding:NSASCIIStringEncoding];
  }
};
#endif
