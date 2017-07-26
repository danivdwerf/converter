#ifndef RESOURCES_H
#define RESOURCES_H

#include <CoreFoundation/CoreFoundation.h>
#include <string>
#include <iostream>
class Resources
{
  private: CFBundleRef mainBundle = CFBundleGetMainBundle();
  public: std::string getFilePath(std::string);
};
#endif
