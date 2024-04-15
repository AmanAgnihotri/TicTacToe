#include "Core/Board/Board.h"

Board::Board()
{
  state = State::Playable;
  count = 0;
}

State Board::getState()
{
  return state;
}

bool Board::apply(int rank, int file, Mark mark)
{
  if (state != State::Playable)
  {
    return false;
  }
  
  if (marks[file][rank] != Mark::Empty)
  {
    return false;
  }
  
  marks[file][rank] = mark;
  count++;
  state = Board::nextState(rank, file, mark);
  
  return true;
}

State Board::nextState(int rank, int file, Mark mark)
{
  const auto side = 3;
  const auto size = side * side;
  const auto threshold = 2 * side - 1;
  
  if (count < threshold)
  {
    return State::Playable;
  }
  
  if (isRankWin(rank, mark) || isFileWin(file, mark))
  {
    return State::Win;
  }
  
  if (isDiagonalWin(rank, file))
  {
    return State::Win;
  }
  
  if (count == size)
  {
    return State::Draw;
  }
  
  return State::Playable;
}

bool Board::isRankWin(int rank, Mark mark)
{
  for (int f = 0; f < 3; f++)
  {
    if (marks[f][rank] != mark)
    {
      return false;
    }
  }
  
  return true;
}

bool Board::isFileWin(int file, Mark mark)
{
  for (int r = 0; r < 3; r++)
  {
    if (marks[file][r] != mark)
    {
      return false;
    }
  }
  
  return true;
}

bool Board::isDiagonalWin(int rank, int file)
{
  if (rank == file)
  {
    if (marks[0][0] == marks[1][1] && marks[1][1] == marks[2][2])
    {
      return true;
    }
  }
  
  if (rank + file == 2)
  {
    if (marks[0][2] == marks[1][1] && marks[1][1] == marks[2][0])
    {
      return true;
    }
  }
  
  return false;
}
