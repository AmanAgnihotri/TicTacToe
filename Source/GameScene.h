#pragma once

#include "axmol.h"
#include "BoardLayer.h"
#include "Core/Game.h"

using namespace ax;

class GameScene final : public Scene
{
public:
  CREATE_FUNC(GameScene);
  
private:
  bool init() override;
  void onTouch(int rank, int file);
  void drawMark(int rank, int file, Mark mark);
  void exit();
  
  Game game;
  BoardLayer* boardLayer;
};
