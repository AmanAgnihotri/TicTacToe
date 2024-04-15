#pragma once

#include "axmol.h"
#include "ui/axmol-ui.h"
#include "Core/Board/Board.h"

using namespace ax;

using OnTouch = std::function<void(int, int)>;

class BoardLayer final : public Layer
{
public:
  CREATE_FUNC(BoardLayer);
  void setOnTouchCallback(OnTouch onTouch);
  void drawX(int rank, int file);
  void drawO(int rank, int file);

private:
  bool init() override;
  
  void setup(const Rect& rect);
  void addTouchListener();
  void drawGrid();
  
  OnTouch onTouch;
  int tileSize;
};
