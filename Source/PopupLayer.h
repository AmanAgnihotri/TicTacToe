#pragma once

#include "axmol.h"
#include "ui/axmol-ui.h"

using namespace ax;

class PopupLayer final : public LayerColor
{
public:
  static PopupLayer* createWithMessage(const std::string& message);
  bool initWithMessage(const std::string& message);
};
