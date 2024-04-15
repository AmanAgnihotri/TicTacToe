#pragma once

#include "axmol.h"

using namespace ax;

class MainMenuScene final : public Scene
{
public:
  CREATE_FUNC(MainMenuScene);
private:
  bool init() override;
};
