#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <fstream>
#include <iostream>
#ifdef __APPLE__
  #include <CoreFoundation/CoreFoundation.h>
#endif

class Resources
{
  #ifdef __APPLE__
    private: CFBundleRef mainBundle = CFBundleGetMainBundle();
    public: std::string getFilePath(std::string);
  #endif
  public: std::string getFileContent(std::string);
  public: bool writeToFile(std::string, std::string);
};
#endif
