#pragma once

#include "Board/Board.h"

enum class GameEvent
{
  AlreadyOccupied,
  Applied,
  WinForX,
  WinForO,
  Draw,
};

class Game final
{
public:
  Game();
  Mark getCurrentMark();
  GameEvent apply(int rank, int file);
private:
  Mark currentMark;
  Board board;
};
