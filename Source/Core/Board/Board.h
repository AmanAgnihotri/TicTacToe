#pragma once

enum class Mark
{
  Empty,
  X,
  O
};

enum class State
{
  Playable,
  Win,
  Draw
};

class Board final
{
public:
  Board();
  State getState();
  bool apply(int rank, int file, Mark mark);
  
private:
  State state;
  Mark marks[3][3];
  int count;
  
  State nextState(int rank, int file, Mark mark);
  bool isRankWin(int rank, Mark mark);
  bool isFileWin(int file, Mark mark);
  bool isDiagonalWin(int rank, int file);
};
