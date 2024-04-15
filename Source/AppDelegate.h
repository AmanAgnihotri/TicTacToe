#pragma once

#include "axmol.h"

using namespace ax;

class AppDelegate final : private Application
{
public:
  bool applicationDidFinishLaunching() override;
  
  void applicationDidEnterBackground() override;
  void applicationWillEnterForeground() override;
};
