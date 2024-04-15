#pragma once

#include "axmol.h"

using namespace ax;

class SplashScene final : public Scene
{
public:
  CREATE_FUNC(SplashScene);
private:
  bool init() override;
  void onEnter() override;
};
